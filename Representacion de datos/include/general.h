#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void printhex(void *puntero, int tamanio);
void print_direccion_memoria(void *puntero, bool validador, char mensaje[]);