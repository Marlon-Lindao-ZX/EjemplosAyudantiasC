#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h> //Libreria Especializada en tiempos

typedef struct Parametro{
    int x;
    int y;
}parameter;

void print_struct_puntero(parameter *puntero);
void print_struct_copia(parameter puntero);