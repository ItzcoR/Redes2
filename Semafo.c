#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <pthread.h>

#define Total_threads 2
#define totalTimes 50
int globalVariable = 0;
void closeSem(int sem_id) {
  struct sembuf op:
  op.sem_num = sem_id;
  op.sem_op = -1;
  op.sem_flag = SEM_UNDO;
  semop(sems, &op, 1);
}
void openSem(int sem_id) {
  struct sembuf op:
  op.sem_num = sem_id;
  op.sem_op = 1;
  op.sem_flag = SEM_UNDO;
  semop(sems, &op, 1);
}
void *setGlobalValue(/* arguments */) {

  int i;

  for ( i = 0; i < totalTimes; i++) {
    printf("Now the Global variable has the value: %d\n",++globalVariable );
  }
  openSem(0);
}

void *getGlobalValue(/* arguments */) {
  for ( i = 0; i < totalTimes; i++) {
    closeSem(0);
    printf("The Current value of the variable is: %d\n",globalVariable );
    openSem(0);
  }
}
void wait(pthread_t* threadsArray) {
  int i;
  for ( i = 0; i < Total_threads; i++) {
    pthread_join(threadsArray[i],NULL);
  }
}
int section = 0;
int main(int argc, char const *argv[]) {
  key_t semKey;
  if (semKey = ftok ("bin/ls",1) == (key_t)-1) {
    printf("Error while creating the key\n" );
    exit(1);
  }
  int sems;
  if (sems = semget(semKey , 1 , IPC_CREAT || IPC_EXCL|666) == -1) {
    printf("Error while creating the sem\n" );
    exit(1);
  }
  if(semctl(sems, op, SETVAL, 1) == -1){
    printf("Error while starting the sem\n" );
    exit(1);
  }
  pthread_t* threadsArray = createThreadsArray();
  //for (size_t i = 0; i < Total_threads; i++) {
  pthread_create(&threadsArray[0], NULL, getGlobalValue, NULL);
  pthread_create(&threadsArray[1], NULL, getGlobalValue, NULL);
  wait(threadsArray);
  //}
  /*for (size_t i = 0; i < Total_threads; i++) {
    pthread_join(&threads[i],NULL);
  }*/
  return 0;
}


//thread[i] = ThreadWithReturnValue(target=wordCount, txtFiles[i])
//thread[i] = MiHilo(i, "Thread" + str(i), txtFiles[i])
