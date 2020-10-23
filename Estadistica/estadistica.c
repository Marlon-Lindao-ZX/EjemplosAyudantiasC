#include "general.h"


float calcular_promedio(int *valores){
    float promedio = 0;
    int acumulador = 0;
    for(int i=0;i<MAX;i++){
        acumulador += valores[i];
    }
    promedio = (float) acumulador/(float) MAX;
    return promedio;
}


float calcular_varianza(int *valores){
    float varianza = 0;
    float promedio = calcular_promedio(valores);
    float acumulador = 0;
    for(int i=0; i<MAX; i++){
        acumulador += calcular_cuadrado(valores[i] - promedio);
    }
    varianza = acumulador/(float) (MAX -1);
    return varianza;
}


float calcular_cuadrado(float valor){
    return valor*valor;
}