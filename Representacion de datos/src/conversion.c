#include "../include/general.h"

void printhex(void *puntero, int tamanio){
    char *pointer = (char *) puntero;

    for(int i=0; i<tamanio;i++){
        printf("%x ", *pointer);
        pointer++;
    }

    printf("\n");
}

void print_direccion_memoria(void *puntero, bool validador, char mensaje[]){
    if(validador)
        printf("La direccion de memoria de la variable tipo %s es: %p\n",mensaje,puntero);
}