#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DoublyLinkedList{
    nodedll *inicio;
    nodedll *fin;
    unsigned long tamano;
}dll;

typedef struct NodeDLL{
    void *elemento;
    struct NodeDLL *siguiente;
    struct NodeDLL *anterior;
}nodedll;

//Funciones principales del DLL
dll* crearDLL();
bool isEmpty(dll *lista);
bool addFirst(dll *lista, void *elemento);
bool addLast(dll *lista, void *elemento);
void* removeFirst(dll *lista);
void* removeLast(dll *lista);
void* getIndex(dll *lista,unsigned long posicion);
void* getElement(dll *lista, void *elemento);
bool destroyDLL(dll *lista);

//Funciones auxiliares del DLL
bool checkIFNULL(void *puntero);
bool checkListAndElementIfNull(dll *lista, void *elemento);
bool checkPosicion(dll *lista,unsigned long posicion);
void *findByIndex(dll *lista, unsigned long posicion);
void *findByElement(dll *lista, void *elemento);
nodedll *crearNodo(void *elemento);
void addWhenEmpty(dll *lista, nodedll *nodo);
void setFirstLastToNull(dll *lista);
