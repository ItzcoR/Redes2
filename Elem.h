#ifndef ELEM_H
#define ELEM_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef int Elem;
int Esmayor(Elem e1,Elem e2){
	return e1>e2;
}
int EsMenor(Elem e1, Elem e2){
	return e1<e2;
}
int IgualesElem(Elem e1,Elem e2){
	return e1==e2;
}
void ImpElem(Elem e){
	printf("%d\t",e );;
}
#endif