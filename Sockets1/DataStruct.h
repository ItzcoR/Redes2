#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct TData{
	int dato;
	long unsigned int* id;
	int* miArr;
}*TData;
TData empty (){return NULL;}
TData definirTdata (int dato,long unsigned int* identificadorHilo,int* Arreglovac,TData l){
	TData t=(TData) malloc(sizeof(TData));
	/*t->dato=dato;
	t->id=identificadorHilo;*/
	t->dato=dato;
	t->id=identificadorHilo;
	t->miArr=Arreglovac;
	return t;
	}
int isempty (TData l) {return l==NULL;}
int getDatoT (TData l) {return l->dato;}
long unsigned int* getIDT (TData l) {return l->id;}
int* getArr (TData l) {return l->miArr;}
