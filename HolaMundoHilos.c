#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "DataStruct.h"

void *funcion(void *arg) {
  //printf("%d",*arg);
  //printf("%u",arg);
  struct TData *myData=(struct TData*)arg;
  int lim=(*myData).dato;
  int i;
  int* fiboarr;
  //int fib[lim+2];
  int * fib;
  fib=malloc(sizeof(int)*(lim));
  fib[0]=0;
  fib[1]=1;
  for ( i = 2; i <= lim; i++) {
    fib[i]=fib[i-1]+fib[i-2];
    if (fib[i]>lim) {
      fib[0]=i;
      //printf("%d\n",fib[0] );
      break;
    }

    //printf("%d\t",fib[i] );
  }
  //for (size_t i = 0; i < fib[0]; i++) {
  //  printf("%d\t",fib[i] );
  //}
/*  int lim=*(int *)getDatoT(arg);
//  printf("%d",lim );
  //TData*  hoe=(TData *)arg;
  //unsigned long int *threadID=getIDT(arg);
  printf("%u\n",*threadID );*/
  myData->miArr= fib;
  fiboarr=getArr(myData);
  printf("Yo soy el hilo  %lu, mi Limite es : %d, mi numero de Elementos es: %d\n",(*myData).id, (*myData).dato, fiboarr[0]);

  //free(arg);
  pthread_exit(&myData);//pthread_exit(Valor de salida del hilo, o NULL);
  //return (void*) fib;

}

int main() {
  int i,nhilos;
  int *limFib;int *fiblims;
  long unsigned int *fibIDS;
  int **fibarrs;
  void *arr;
	long unsigned int *ji;
  pthread_t *thread;
	TData* datosHilot;
  TData  dataFib;
  int * prueba;
  printf("Numero de hilos a crear\n" );
  scanf("%d", &nhilos );
  //printf("%d",nhilos );
  thread=(pthread_t *) malloc(sizeof(pthread_t) * nhilos);
  limFib=malloc(sizeof(int)* nhilos);
  fibarrs=malloc(sizeof(int*)* nhilos);
  fibIDS=malloc(sizeof(long unsigned int)* nhilos);
  fiblims=malloc(sizeof(int)* nhilos);
  datosHilot=malloc(sizeof(struct TData)* nhilos);
  //printf("Limite de la serie de Fibonacci\n" );
  //scanf("%d", &limFib );
  for (size_t i = 0; i < nhilos; i++) {
    printf("Limite de la serie de Fibonacci para el hilo %d\n",i+1 );
    scanf("%d", &limFib[i] );
    fibarrs[i]=malloc(sizeof(int)*limFib[i]);
  }
  for (size_t i = 0; i < nhilos; i++) {
    datosHilot[i]=definirTdata(limFib[i],&thread[i],fibarrs[i],datosHilot[i]);
    printf("DatosHilos:%d, limFib: %d threadID: %lu\n",datosHilot[i],limFib[i],&thread[i]);
    pthread_create(&thread[i],NULL,funcion,(void *)datosHilot[i]);
    //pthread_create(Nombre del hilo, Caracteristicas, funcion, Elementos de la funcion)
  }
  for (size_t i = 0; i < nhilos; i++) {
    pthread_join(thread[i],(void**)datosHilot);
    //dataFib=(struct TData *)arr;
    //fibarrs[i]=(int*)getArr(datosHilot[i]);
    //prueba=getArr(datosHilot[i+1]);
    fibIDS[i]=(long unsigned int)getIDT(datosHilot[i]);
    fiblims[i]=(int)getDatoT(datosHilot[i]);
    printf("\nID del hilo: %lu, lim del hilo: %d\n",fibIDS[i],fiblims[i] );
    //printf("tamaño del array: %d\n",prueba[0]);
    /*for (size_t j = 2; j <prueba[0] ; j++) {
      printf("%d\t" ,prueba[j]);
    }*/
  }
  for (size_t i = 1; i < nhilos; i++) {
    prueba=getArr(datosHilot[i]);
    fibIDS[i]=(long unsigned int)getIDT(datosHilot[i]);
    fiblims[i]=(int)getDatoT(datosHilot[i]);
    printf("\nID del hilo: %lu, lim del hilo: %d\n",fibIDS[i],fiblims[i] );
    printf("tamaño del array: %d\n",prueba[0]);
    for (size_t j = 2; j <prueba[0] ; j++) {
      printf("%d\t" ,prueba[j]);
    }

    //printf("tamaño del array: %d",sizeof(*arr) );
    //pthread_join(thread[i],Valores esperados de la resolucion void **retval)
  }
  free(thread);
  free(fiblims);
  free(fibarrs);
  free(fibIDS);
  free(datosHilot);
  free(dataFib);
  return 0;
}
