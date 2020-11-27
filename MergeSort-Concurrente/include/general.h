#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#define SIZE 128

typedef struct colaTDA{
	unsigned long tamano;
	struct nodo_colaTDA *inicio;
	struct nodo_colaTDA *fin;
} cola;

typedef struct nodo_colaTDA{
	void *elemento;
	struct nodo_colaTDA *siguiente;
	struct nodo_colaTDA *anterior;
} nodo_cola;

//Funciones del main
bool cambiar_string_a_int(char buffer[], int *puntero);
void obtenerValor(int *puntero, char *buffer, size_t tam);
void print_error(char *buffer);

//Cola
cola *crear_cola();
int encolar(cola *mi_cola, void * elemento);
void *decolar(cola *mi_cola);
unsigned long tamano_cola(cola *mi_cola);
unsigned long posicion_cola(cola *mi_cola, void *elemento);
int destruir_cola(cola *mi_cola);

//Auxiliares para Cola
bool isEmpty(cola *mi_cola);
bool checkIfNull(void *elemento);
bool checkCola(cola *mi_cola);
bool checkIfIntEqual(void *a, void *b);
bool checkFirst(cola *mi_cola);
bool checkFirstEqualLast(cola *mi_cola);
void initCola(cola *mi_cola);
void setFirstAndLastToNull(cola *mi_cola);
void changeFirst(cola *mi_cola, nodo_cola *node);
void setFirst1(cola *mi_cola,nodo_cola *node);
void setFirst2(cola *mi_cola,nodo_cola *node);
unsigned long findElemento(cola *mi_cola, void *elemento);

//Opciones
void manejar_opciones(int argc, char **argv, char **archivo);
void print_help(char *programa);