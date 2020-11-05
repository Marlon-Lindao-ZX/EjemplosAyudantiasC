#include "../include/general.h"

void printhex(void *puntero, int tamanio){
    char *pointer = (char *) puntero;

    for(int i=0; i<tamanio;i++){
        printf("%x ", *pointer);
        pointer++;
    }

    printf("\n");
}