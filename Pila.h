#include "Elem.h"
typedef struct Nodo{
	Elem dato;
		struct Nodo *sig;
		   }*Pila;
Pila empty (){return NULL;}
Pila push (Elem e, Pila l){
	Pila t=(Pila) malloc(sizeof(struct Nodo));
	t->dato=e;
	t->sig=l;
	return t;
	}
int isempty (Pila l) {return l==NULL;}
Elem top (Pila l) {return l->dato;}
Pila pop (Pila l) {return l->sig;}