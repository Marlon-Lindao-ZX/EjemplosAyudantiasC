#include "general.h"

int cambiar_string_a_int(){
    char input[MAX2];
    printf("Ingrese un valor numerico: ");
    scanf("%s",input);
    int conversion = atoi(input);
    while(conversion == 0 && strcmp(input,"0") != 0){
        printf("Error, valor no es numerico\n");
        memset(input,0,MAX2);
        printf("Ingrese un valor numerico: ");
        scanf("%s",input);
        conversion = atoi(input);
    }
    return conversion;
}

