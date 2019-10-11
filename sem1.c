#include<stdio.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>

#define Total_threads 2
#define PRODUCTOR1 0
#define PRODUCTOR2 1
#define CONSUMIDOR1 2
#define CONSUMIDOR2 3
//int section = 0,sems;
int semid;
char seccion_critica[2][10];

const int num_productores_consimidores = 3
const int num_producciones_x_productor = 20 ;
const int tam_operacion = 1;
struct sembuf operacion;

void *hilo_productor(void *args );


void *hilo_consumidor(void *args );
void *hilo_consumidor2(void *args );
void *hilo_consumidor3(void *args );
void openSem(int sem_id){
	struct sembuf op;
	op.sem_num = sem_id;
	op.sem_op = 1;
	op.sem_flg = SEM_UNDO;
	semop(sems, &op, 1);
}
void closeSem(int sem_id){
	struct sembuf op;
	op.sem_num = sem_id;
	op.sem_op = -1;
	op.sem_flg = SEM_UNDO;
	semop(sems, &op, 1);
}
void * tenedor(void){
	for (int i = 0; i < 50; ++i){
		closeSem(0);
		printf("El valor de la seccion es: %d\n",section++);
		openSem(1);
	}
}
void * tenedor2(void){
	for (int i = 0; i < 50; ++i){
		closeSem(1);
		printf("El valor obtenido es: %d\n",section);
		openSem(0);
	}
}
int main(int argc, char const *argv[]){
	//int sems;
	key_t llave;
	pthread_t productor1,productor2,productor3;
	pthread_t consumidor1,consumidor2,consumidor3;
	llave = ftok("/bin/ls",1)
	if((semKey = ftok("/bin/ls",1)) == -1){
		printf("Error creando la llave prro\n");
		exit(1);
	}
	if((sems=semget(semKey,4,IPC_CREAT|IPC_EXCL|0600))==-1){
		printf("Error al crear los semaforos prro\n");
		exit(1);
	}
	if(semctl(sems,0,SETVAL,1)==-1){
		printf("Error inicializando los semaforos prro\n");
		exit(1);
	}
	pthread_t * threads = (pthread_t *)malloc(sizeof(pthread_t)*Total_threads);
	pthread_create(&threads[0], NULL, (void *)tenedor, NULL);
	pthread_create(&threads[1], NULL, (void *)tenedor2, NULL);
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);
	return 0;
}

void *hilo_productor(void *args ){
	char produccion[10] =;
	int i, j;
	switch (*(int)args) {
		case 0:
			produccion = "Hola mundo";
		case 1:
			produccion = "2222222222";
		case 2:
			produccion = "3333333333";
	}
	for ( i = 0; i < num_producciones_x_productor; i++) {
		int indice_seccion = 0;
		while (true) {
			if (indice_seccion >= num_secciones)
					indice_seccion = 0;
			 {
				cerramos_semaforo(PRODUCTOR1);

				//ZONA seccion_critica
				seccion_critica[j] = producir;
				//printf("Soy el hilo: %u y puse a i con el valor: %d\n",(unsigned int) pthread_self(), i++ );

				abrimos_semaforo(j+1);
				break;
			}
			else if((semctl(semid, PRODUCTOR2, GETVAL)) != 0)){
				cerramos_semaforo(PRODUCTOR2);

				//ZONA seccion_critica
				seccion_critica[j] = producir;
				//printf("Soy el hilo: %u y puse a i con el valor: %d\n",(unsigned int) pthread_self(), i++ );

				abrimos_semaforo(CONSUMIDOR2);
				break;
			}
		}


	}
	semctl( semid, 0, IPC_RMID,0);
	pthread_exit();
}
