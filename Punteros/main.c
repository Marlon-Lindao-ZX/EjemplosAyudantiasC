#include <stdio.h>
#include <stdlib.h>


void main(){

    char x = 88;
    char y = 89;
    char z = 90;
    char a = 91;

    char *puntero = &x;
    int arreglos[100]; // --> int *arreglos

    //arreglos[1] === *(arreglos + 1) --> Son equivalentes

    /*
    La reglas de desplazamiento del puntero(sumar o restarle por algun valor) obedecer al tipo de dato que esta referenciando
    y asi mismo cuando se usa el * para obtener el valor(Esto quiere decir que segun el tipo de dato, el puntero va a 
    seleccionar los bytes que necesita para formar su valor)
    */

    printf("El valor donde esta apuntando el puntero es: %d\n", *puntero);
    printf("El valor donde esta apuntando el puntero es: %d\n", puntero[1]);
    printf("La direccion de memoria que almacena puntero es: %p\n", puntero);
    

    puntero = &y;
    printf("El valor donde esta apuntando el puntero es: %c\n", *puntero);
    printf("La direccion de memoria que almacena puntero es: %p\n", puntero);
    printf("%p\n",&z);
    printf("%p\n",&a);

    short *puntero2 = &x;
    printf("El valor short que almacena puntero es: %p\n", puntero2);

    int *puntero3 = &x;
    printf("El valor int que almacena puntero es: %p\n", puntero3);
}