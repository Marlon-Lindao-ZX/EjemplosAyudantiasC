#include "dll.h"

int main(){

    dll *lista = crearDLL();

    int *pruebas = (int *) malloc(20*sizeof(int));
    int *resultado;

    printf("1\n");

    for(int i=0; i<20;i++){
        pruebas[i] = 10 + i*i;
        addFirst(lista, (void *) &pruebas[i], sizeof(int));
    }

    printf("Tamaño de la lista es: %ld\n", getTamano(lista));
    printf("2\n");
    for(int i=0; i<20;i++){
        resultado = (int *) getElementByIndex(lista,(long) i);
        if(resultado != NULL)
            printf("%d\n", *resultado);
    }
    printf("3\n");
    for(int i=0; i<20;i++){
        printf("Removiendo elemento: %d\n", *((int *) removeFirst(lista)));
    }

    free(pruebas);
    return 0;
}