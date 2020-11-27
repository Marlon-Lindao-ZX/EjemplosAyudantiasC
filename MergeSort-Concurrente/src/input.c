#include "../include/general.h"

bool cambiar_string_a_int(char *buffer, int *puntero){
    int conversion = atoi(buffer);
    
    if (strcmp(buffer, "0") != 0 && conversion == 0){
        print_error("No ingreso un numero, tiene que ingresar un numero\n");
        return false;
    }
    *puntero = conversion;
    return true;
}

void obtenerValor(int *puntero, char *buffer, size_t tam){
    
    do{
        memset(buffer,0,tam);
        printf("Ingrese el valor a buscar: ");
        fgets(buffer,tam,stdin);

    }while(!cambiar_string_a_int(buffer,puntero));
}

void print_error(char *buffer){
    fprintf(stderr,"%s",buffer);
}