#include "../include/general.h"

int main(int argc, char **argv){

    char *archivo = NULL;

    manejar_opciones(argc,argv,&archivo);

    char buffer[SIZE];

    cola *mi_cola = crear_cola();

    int *elemento = NULL;
    int conversion = 0;

    printf("Ingrese un elemento a la cola (entre un numero): ");

    while (fgets(buffer,SIZE,stdin) != NULL)
    {
        
        if (strcmp(buffer, "x\n") == 0)
            break;

        if(cambiar_string_a_int(buffer,&conversion)){
            elemento = (int *) malloc(sizeof(int));
            *elemento = conversion;
            encolar(mi_cola,(void *) elemento);
        }
        memset(buffer, 0, SIZE);

        printf("Ingrese un elemento a la cola (entre un numero): ");
    }

    printf("La cola tiene %ld elementos\n",tamano_cola(mi_cola));
}