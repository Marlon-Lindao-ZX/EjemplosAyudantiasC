#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 5
#define MAX2 100
#define CONSTANTE "HOLA MUNDO"

typedef struct estadistica{
    float media;
    float varianza;
}estd_t;

int cambiar_string_a_int();
float calcular_promedio(int *valores);
float calcular_varianza(int *valores);
float calcular_cuadrado(float valor);