#include "general.h"


int main(){
    estd_t resultado;

    int valores[MAX];
    
    for(int i=0; i<MAX; i++){
        valores[i] = cambiar_string_a_int();
        printf("%d\n",valores[i]);
    }

    resultado.media = calcular_promedio(valores);
    resultado.varianza = calcular_varianza(valores);

    printf("El promedio es: %f\n", resultado.media);
    printf("La varianza es igual a: %f\n", resultado.varianza);

    return 0;
    

}


