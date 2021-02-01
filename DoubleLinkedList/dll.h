#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DoublyLinkedList{
    struct NodeDLL *inicio;
    struct NodeDLL *fin;
    unsigned long tamano;
}dll;

typedef struct NodeDLL{
    void *elemento;
    size_t tamano;
    struct NodeDLL *siguiente;
    struct NodeDLL *anterior;
}nodedll;

//Funciones principales del DLL
dll* crearDLL();
bool isEmpty(dll *lista);
unsigned long getTamano(dll *lista);
bool addFirst(dll *lista, void *elemento, size_t tamano);
bool addLast(dll *lista, void *elemento, size_t tamano);
bool insertDLL(dll *lista, void *elemento, size_t tamano, unsigned long posicion);
void* removeFirst(dll *lista);
void* removeLast(dll *lista);
void* removeDLL(dll *lista, unsigned long posicion);
void* getElementByIndex(dll *lista,unsigned long posicion);
long getIndex(dll *lista, void *elemento, size_t tamano);
bool destroyDLL(dll *lista);

//Funciones auxiliares del DLL
bool checkIFNULL(void *puntero);
bool checkListAndElementIfNull(dll *lista, void *elemento);
bool checkPosicion(dll *lista,unsigned long posicion);
void *findByIndex(dll *lista, unsigned long posicion);
long findByElement(dll *lista, void *elemento, size_t tamano);
nodedll *crearNodo(void *elemento, size_t tamano);
void addWhenEmpty(dll *lista, nodedll *nodo);
void setFirstLastToNull(dll *lista);
bool checkIfEquals(void *a, void *b, size_t tamanoA, size_t tamanoB);
bool recorrerPunteros(void *a, void *b, size_t tamano);
