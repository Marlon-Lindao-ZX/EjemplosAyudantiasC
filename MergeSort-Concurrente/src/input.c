#include "../include/general.h"

bool cambiar_string_a_int(char *buffer, int *puntero){
    int conversion = atoi(buffer);
    if (strcmp(buffer, "0") != 0 && strcmp(buffer, "00") != 0 && strcmp(buffer, "000") != 0 &&
        strcmp(buffer, "0000") != 0 && conversion == 0){
        print_error("Error de conversion de string a numero\n");
        printf("%s\n",buffer);
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

int exponente_2(int numero){
    if(numero % 2 != 0)
        numero++;
    int contador = 0;
    do{
        if(numero / 2 > 0)
            contador++;
        numero /= 2;
    }while(numero / 2 > 0);
    return contador;
}

int obtener_potencia(int numero, int exponente){
    int resultado = numero;

    if(exponente == 1)
        return numero;
    else if(exponente == 0)
        return 1;

    for(int i =1; i<exponente; i++)
        resultado *= resultado;

    return resultado;
}

void print_error(char *buffer){
    fprintf(stderr,"%s",buffer);
}

void end_with_error(char *buffer){
    print_error(buffer);
    exit(-1);
}