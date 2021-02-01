#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 1024

typedef struct colaTDA{
	unsigned long tamano;
	struct nodo_colaTDA *first;
	struct nodo_colaTDA *last;
} cola;

typedef struct nodo_colaTDA{
	void *elemento;
	struct nodo_colaTDA *siguiente;
	struct nodo_colaTDA *anterior;
} nodo_cola;

cola *crear_cola();
int encolar(cola *mi_cola, void * elemento);
void *decolar(cola *mi_cola);
unsigned long tamano_cola(cola *mi_cola);
unsigned long posicion_cola(cola *mi_cola, void *elemento);
int destruir_cola(cola *mi_cola);



