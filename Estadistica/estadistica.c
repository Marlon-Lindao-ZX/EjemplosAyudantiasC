#include "general.h"

float calcular_promedio(int *valores){
    float promedio = 0;
    int acumulador = 0;
    for(int i=0;i<MAX;i++){
        acumulador += valores[i];
    }
    promedio = (float) acumulador/(float) MAX;
    printf("%f\n",promedio);
    return promedio;

}