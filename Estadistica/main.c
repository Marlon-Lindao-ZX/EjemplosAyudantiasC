#include "general.h"


int main(){
    estd_t resultado;
    int n = 10;

    int valores[MAX];

    for(int i=0; i<MAX; i++){
        valores[i] = cambiar_string_a_int();
        printf("%d\n",valores[i]);
    }

    calcular_promedio(valores);
    

}


