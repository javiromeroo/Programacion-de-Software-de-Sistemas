#include <stddef.h>

#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {  
  if (t == NULL){
    return; //caso base de si es un arbol vacio
  }
  //si no primero aplicamos funcion a la izq recursivamente
  asignarPrev(t->izq, pprev);
  //ahora aplicamos la ayuda  
  t->prev=*pprev; //su previo va a ser *pprev
  t->prox=NULL; //asignamos null al prox por ahora
  if ((t->prev) != NULL){ //si el nodo previo a t no es null
    //t es prox de prev a t 
    (t->prev)->prox = t;  
  }
  //antes de continuar el recorrido asignar t a *pprev
  *pprev = t; 
  asignarPrev(t->der, pprev);//continuar recursion con lado derecho
}