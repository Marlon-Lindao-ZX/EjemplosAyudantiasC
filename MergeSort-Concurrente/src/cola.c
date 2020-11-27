#include "../include/general.h"

cola *crear_cola(){
	cola *mi_cola = (cola *) malloc(sizeof(cola));

	initCola(mi_cola);
	
	return checkIfNull((void *) mi_cola) ? NULL : mi_cola;
}

int encolar(cola *mi_cola, void * elemento){
	if(checkIfNull(elemento) || checkIfNull((void *) mi_cola)) 
		return -1;

	nodo_cola *nodo = (nodo_cola *) malloc(sizeof(nodo_cola));
	nodo->elemento = elemento;

	if(isEmpty(mi_cola))
		setFirst1(mi_cola,nodo); 
	else 
		setFirst2(mi_cola,nodo);

    mi_cola->tamano++;

	return 0;
}

void *decolar(cola *mi_cola){

	if(checkFirst(mi_cola)) 
		return NULL;

	nodo_cola *temp = mi_cola->inicio;
	void *data = temp->elemento;

	if(checkFirstEqualLast(mi_cola))
		setFirstAndLastToNull(mi_cola);
	else 
		changeFirst(mi_cola,temp);

	free(temp);

    mi_cola->tamano--;

	return data;
}

unsigned long posicion_cola(cola *mi_cola, void *elemento){
	return checkIfNull(elemento) || checkCola(mi_cola) ? -1: findElemento(mi_cola,elemento);
}

int destruir_cola(cola *mi_cola){
	if(isEmpty(mi_cola)) {
		free(mi_cola);
		return 0;
	}
	return -1;
}

unsigned long tamano_cola(cola *mi_cola){
	return mi_cola->tamano;
}

bool isEmpty(cola *mi_cola){
	return mi_cola->tamano == 0;
}

bool checkIfNull(void *elemento){
	return elemento == NULL;
}

bool checkCola(cola *mi_cola){
	return isEmpty(mi_cola) || checkIfNull((void *) mi_cola);
}

bool checkIfIntEqual(void *a, void *b){
	return *((int *) a) == *((int *)b);
}

bool checkFirst(cola *mi_cola){
	return checkCola(mi_cola) || mi_cola->inicio == NULL;
}

bool checkFirstEqualLast(cola *mi_cola){
	return mi_cola->inicio == mi_cola->fin;
}

void setFirst1(cola *mi_cola,nodo_cola *node){
	mi_cola->inicio = mi_cola->fin = node;
	node->siguiente = NULL;
	node->anterior = NULL;
}

void setFirst2(cola *mi_cola,nodo_cola *node){
	mi_cola->fin->siguiente = node;
	node->anterior = mi_cola->fin;
	node->siguiente = NULL;
    mi_cola->fin = node;
}

void setFirstAndLastToNull(cola *mi_cola){
	mi_cola->inicio = NULL;
	mi_cola->fin = NULL;
}

void initCola(cola *mi_cola){
	mi_cola->tamano=0;
	setFirstAndLastToNull(mi_cola);
}

void changeFirst(cola *mi_cola, nodo_cola *node){
	mi_cola->inicio = mi_cola->inicio->siguiente;
    mi_cola->inicio->anterior = NULL;
    node->siguiente = NULL;
}

unsigned long findElemento(cola *mi_cola, void *elemento){
	unsigned long posicion = 0;
	nodo_cola *temporal = mi_cola->inicio;
	while(temporal != NULL){
		if(checkIfIntEqual(temporal->elemento,elemento)) {
			return posicion;
		}
		posicion++;
		temporal = temporal->siguiente;
	}
	return -1;
}

