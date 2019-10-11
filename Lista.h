#include "Elem.h"
typedef struct Nodo1{
	Elem dato;
		struct Nodo1 *sig;
		   }*Lista;
Lista vacia (){return NULL;}
Lista cons (Elem e, Lista l){
	Lista t=(Lista) malloc(sizeof(struct Nodo1));
	t->dato=e;
	t->sig=l;
	return t;
	}
int esvacia (Lista l) {return l==NULL;}
Elem cabeza (Lista l) {return l->dato;}
Lista resto (Lista l) {return l->sig;}
int NumElem (Lista l){
	if(esvacia(l))
	{
		return 0;
	}
	else
	return 1+NumElem(resto(l));}
void ImpLista(Lista l){
	if(!esvacia(l)){
		ImpElem(cabeza(l));
		ImpLista(resto(l));
	}
}
int estaen(Elem e,Lista l){
	if(esvacia(l))
	{
		return 0;
	}
	else if(e==cabeza(l)){
		return 1;
	}
	else 
	return estaen(e,resto(l));
}
Lista PegaListas(Lista l1,Lista l2){

	if(esvacia(l1))
		return l2;
	else
		return cons(cabeza(l1),PegaListas(resto(l1),l2));	
}
Lista InvierteLista(Lista l)
{
	if(esvacia(l))
		return l;
	else
		return PegaListas(InvierteLista(resto(l)), cons(cabeza(l), vacia()));
}
int SonIguales(Lista l1, Lista l2)
{
	if (esvacia(l1) && esvacia(l2))
		return 1;
	else 
		if (esvacia(l1) && !esvacia(l2))
			return 0;
			else
				if (!esvacia(l1) && esvacia(l2))
					return 0;
					else
						return (IgualesElem(cabeza(l1), cabeza(l2)) && SonIguales(resto(l1), resto(l2)));
		
}

int Palindroma(Lista l)
{
	SonIguales(l, InvierteLista(l));
}

Lista InsOrd(Elem e, Lista l)
{
	if (esvacia(l))
		return cons(e, vacia());
		else
			if (EsMenor(e, cabeza(l)))
				return cons(e, cons(cabeza(l), resto(l)));
				else
					return cons(cabeza(l), InsOrd(e, resto(l)));
}


Lista Ordena(Lista l)
{
	if(esvacia(l))
		return l;
	else
		return InsOrd(cabeza(l), Ordena(resto(l)));
}

Lista OrdenaDes(Lista l)
{
	InvierteLista(Ordena(l));
}