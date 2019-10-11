#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Pila.h"
int main(int argc, char const *argv[]) {
  int n,topepila;
  Pila pila1={push(4,(push(3,empty())))};
  printf("Hola, dame un numero\n");
  scanf("%d",&n );
  //printf("Valor: %d\n",n );
  pila1=push(n,pila1);
  topepila=isempty(pop(pop(pop(pila1))));
  printf("El 3er elemento de la pila es %d\n",topepila);
  return 0;
}
