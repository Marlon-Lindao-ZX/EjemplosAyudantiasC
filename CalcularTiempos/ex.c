#include "general.h"


int f = 20;

void print_struct_puntero(parameter *puntero){
    printf("%d\n",puntero->x);
    printf("%d\n",puntero->y);
}

void print_struct_copia(parameter puntero){
    printf("%d\n",puntero.x);
    printf("%d\n",puntero.y);
}