#include "general.h"

dll* crearDLL(){
    dll *lista = (dll *) malloc(sizeof(dll));
    lista->inicio = lista->fin = NULL;
    lista->tamano = 0;
    return lista;
}

nodedll *crearNodo(void *elemento){
    nodedll *nodo = (nodedll *) malloc(sizeof(nodedll));
    nodo->elemento = elemento;
    nodo->anterior = nodo->siguiente = NULL;
    return nodo;
}

unsigned long getTamano(dll *lista){
    return lista->tamano;
}

bool addFirst(dll *lista, void *elemento){
    if(checkListAndElementIfNull(lista,elemento)) return false;
    nodedll *nuevo = crearNodo(elemento);
    if(isEmpty(lista)) addWhenEmpty(lista,nuevo);
    else{
        lista->inicio->anterior = nuevo;
        nuevo->siguiente = lista->inicio;
        lista->inicio = nuevo;
    }
    return true;

}

bool addLast(dll *lista, void *elemento){
    if(checkListAndElementIfNull(lista,elemento)) return false;
    nodedll *nuevo = crearNodo(elemento);
    if(isEmpty(lista)) addWhenEmpty(lista,nuevo);
    else{
        lista->fin->siguiente = nuevo;
        nuevo->anterior = lista->fin;
        lista->fin = nuevo;
    }
    return true;
}

void* removeFirst(dll *lista){
    if(checkIFNULL((void *) lista) || isEmpty(lista)) return NULL;
    nodedll *temporal = lista->inicio->siguiente;
    void *elemento = lista->inicio->elemento;
    free(lista->inicio);
    lista->tamano--;
    if(isEmpty(lista)) setFirstLastToNull(lista);
    else lista->inicio = temporal;
    return elemento;
}

void* removeLast(dll *lista){
    if(checkIFNULL((void *) lista) || isEmpty(lista)) return NULL;
    nodedll *temporal = lista->fin->anterior;
    void *elemento = lista->fin->elemento;
    free(lista->fin);
    lista->tamano--;
    if(isEmpty(lista)) setFirstLastToNull(lista);
    else lista->fin = temporal;
    return elemento;

}

void* getIndex(dll *lista,unsigned long posicion){
    return checkIFNULL((void *) lista) || isEmpty (lista) || !checkPosicion(lista,posicion) ? NULL:findByIndex(lista,posicion);
}

void* getElement(dll *lista, void *elemento){
    return checkListAndElementIfNull(lista,elemento) || isEmpty (lista) ? NULL:findByElement(lista,elemento);
}

bool destroyDLL(dll *lista){
    if(isEmpty(lista)){
        free(lista);
        return true;
    }
    return false;
}

bool checkPosicion(dll *lista,unsigned long posicion){
    return posicion >= 0 && posicion < lista->tamano;
}

bool checkListAndElementIfNull(dll *lista, void *elemento){
    return checkIFNULL((void *) lista) || checkIFNULL(elemento);
}

bool checkIFNULL(void *puntero){
    return puntero == NULL;
}

bool isEmpty(dll *lista){
    return lista->tamano == 0;
}

void addWhenEmpty(dll *lista, nodedll *nodo){
    lista->inicio = lista->fin = nodo;
}

void setFirstLastToNull(dll *lista){
    lista->inicio = lista->fin = NULL;
}

void *findByIndex(dll *lista, unsigned long posicion){
    unsigned long contador = 0;
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(contador == posicion) return temp->elemento;
        contador++;
    }
    return NULL;
}

void *findByElement(dll *lista, void *elemento){
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(temp->elemento == elemento) return temp->elemento;
    }
    return NULL;
}
