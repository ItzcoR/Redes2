#include "headers.h"

int prod_cons_semid;
int global_consumed = 0;

pthread_t producers[NUM_PROD];
pthread_t consumers[NUM_CONS];

producer_data producers_data[NUM_PROD];
consumer_data consumers_data[NUM_CONS];
section_data sections[NUM_SECTIONS];

FILE *output_files[NUM_PRODUCTIONS];

int main(int argc, char const *argv[])
{
	init_global_producer_consumer_sems();
	generate_sections();

	open_files();

	init_threads();
	join_threads();

	close_files();

	return 0;
}

void open_files()
{
	// Erase previous used files.
	// int r = system("rm output_files/out*");
	//printf("%d\n", r);

	for (int i = 0; i < NUM_SECTIONS; i++)
	{
		char filename[50];

		snprintf(filename, sizeof(filename), "output_files/output_section%d.txt", i);

		output_files[i] = fopen(filename, "w");

		if (output_files[i] == NULL)
		{
			raise_error("Open files");
		}
	}
}

void close_files()
{
	for (int i = 0; i < NUM_SECTIONS; i++)
	{
		fclose(output_files[i]);
	}
}

void generate_sections()
{
	for (int i = 0; i < NUM_SECTIONS; i++)
	{
		// Generate key for sems.
		key_t key = generate_key(2 + i);

		// Create producer/consumer sems for section.
		int semid = semget(key, 2, IPC_CREAT | 0660);

		// Open sem for producer and close for any consumer.
		init_sems(semid, 1, 0);

		sections[i].semid = semid;
	}
}

void init_global_producer_consumer_sems()
{
	// Generate key for sems.
	key_t key = generate_key(1);

	// Create producer/consumer sems.
	prod_cons_semid = semget(key, 2, IPC_CREAT | 0660);

	if (prod_cons_semid == -1)
	{
		raise_error("Error while creating producer/consumer sems");
	}

	/* 

	Initilize sems for producers and consumers.

	Producers sem set to number of sections.
	Close consumers until there's any data.

	*/
	init_sems(prod_cons_semid, NUM_SECTIONS, 0);
}

void init_sems(int semid, int prod_val, int cons_val)
{
	if (semctl(semid, PROD_SEM_IDX, SETVAL, prod_val) == -1 || semctl(semid, CONS_SEM_IDX, SETVAL, cons_val) == -1)
	{
		raise_error("Set sem init val");
	}
}

void println(char *text)
{
	printf("%s\n", text);
}

key_t generate_key(int id)
{
	key_t key;

	// Catch error.
	if (key = ftok("/tmp", id) == -1)
	{
		raise_error("Error while creating key");
	}

	return key;
}

void raise_error(char *msg)
{
	perror(msg);
	exit(-1);
}

void *generate_producers_threads()
{
	for (int i = 0; i < NUM_PROD; i++)
	{
		producers_data[i].index = i;
		pthread_create(&producers[i], NULL, (void *)producer_thread, &producers_data[i]);
	}
}

void *generate_consumers_threads()
{
	for (int i = 0; i < NUM_CONS; i++)
	{
		consumers_data[i].index = i;

		pthread_create(&consumers[i], NULL, (void *)consumer_thread, &consumers_data[i]);
	}
}

void init_threads()
{
	pthread_t gen_prod_thread, gen_cons_thread;

	// Async create producers and consumers.
	pthread_create(&gen_prod_thread, NULL, generate_producers_threads, NULL);
	pthread_create(&gen_cons_thread, NULL, generate_consumers_threads, NULL);

	pthread_join(gen_prod_thread, NULL);
	pthread_join(gen_cons_thread, NULL);
}

void join_threads()
{
	for (int i = 0; i < NUM_PROD; i++)
	{
		pthread_join(producers[i], NULL);
	}

	for (int i = 0; i < NUM_CONS; i++)
	{
		pthread_join(consumers[i], NULL);
	}
}

void increment_sem(int semid, int semidx)
{
	struct sembuf operation;

	operation.sem_num = semidx;
	operation.sem_op = 1;
	operation.sem_flg = 0;

	semop(semid, &operation, 1);
}

void decrement_sem(int semid, int semidx)
{
	struct sembuf operation;

	operation.sem_num = semidx;
	operation.sem_op = -1;
	operation.sem_flg = 0;

	semop(semid, &operation, 1);
}

void *producer_thread(producer_data *data)
{
	int produced = 0;
	pthread_t thread_id = pthread_self();

	while (produced < NUM_PRODUCTIONS)
	{
		// Enter to sections.
		decrement_sem(prod_cons_semid, PROD_SEM_IDX);

		// Search for open section.
		for (int i = 0; i < NUM_SECTIONS && produced < NUM_PRODUCTIONS; i++)
		{
			section_data *section = &sections[i];
			int semid = section->semid;

			// Check if sem is open on i-th section.
			if (semctl(semid, PROD_SEM_IDX, GETVAL) > 0)
			{
				// Close producer sem on i-th section.
				decrement_sem(semid, PROD_SEM_IDX);

				// BEGIN CRITICAL AREA

				snprintf(section->value, (TAM_BUFF - 1) * sizeof(char), "Producer %d in thread %d produced %d", data->index, (int)thread_id, produced);

				// END CRITICAL AREA

				// Open consumer sem on i-th section.
				increment_sem(semid, CONS_SEM_IDX);
				increment_sem(prod_cons_semid, CONS_SEM_IDX);

				// Increment produced count.
				produced++;

				// break;
			}
		}

		// Exit sections.
		increment_sem(prod_cons_semid, PROD_SEM_IDX);
	}
}

void *consumer_thread(consumer_data *data)
{
	pthread_t thread_id = pthread_self();

	while (global_consumed < NUM_PRODUCTIONS * NUM_PROD)
	{
		// Enter to sections.
		decrement_sem(prod_cons_semid, CONS_SEM_IDX);

		// Search for open section.
		for (int i = 0; i < NUM_SECTIONS && global_consumed < NUM_PRODUCTIONS * NUM_PROD; i++)
		{
			section_data section = sections[i];
			int semid = section.semid;

			// Check if sem is open on i-th section.
			if (semctl(semid, CONS_SEM_IDX, GETVAL) > 0)
			{
				// Close consumer sem on i-th section.
				decrement_sem(semid, CONS_SEM_IDX);

				// BEGIN CRITICAL AREA

				FILE *file = output_files[i];

				fprintf(file, "%s consumed by consumer %d in thread %d\n", section.value, i, (int)thread_id);

				global_consumed++;

				// END CRITICAL AREA

				// Open producer sem on i-th section.
				increment_sem(semid, PROD_SEM_IDX);
				increment_sem(prod_cons_semid, CONS_SEM_IDX);

				// break;
			}
		}

		// Exit sections.
		increment_sem(prod_cons_semid, CONS_SEM_IDX);
	}
}
