#include "../include/cola.h"

int main()
{

    char buffer[MAX];
    char *mask = buffer;
    size_t size = MAX;
    size_t l;

    cola *nuevo = crear_cola();

    int *puntero = NULL;

    while ((l = getline(&mask, &size, stdin)) != -1)
    {
        
        if (strcmp(mask, "x\n") == 0)
            break;

        int value = atoi(mask);
        if (value == 0 && strcmp(mask, "0") != 0)
        {
            fprintf(stderr,"No es un numero\n");
        }
        else
        {
            puntero = (int *) malloc(sizeof(int));
            *puntero = value;
            encolar(nuevo,(void *) puntero);
        }
        memset(mask, 0, MAX);
    }

    printf("La cola tiene %ld elementos\n",tamano_cola(nuevo));
    printf("Elemento a buscar: ");

    getline(&mask, &size, stdin);
    int value = atoi(mask);

    while(value == 0 && strcmp(mask, "0") != 0)
    {
        fprintf(stderr,"Valor ingresado no es un numero\n");
        
        memset(mask, 0, MAX);
        
        printf("Elemento a buscar: ");
        getline(&mask, &size, stdin);
        
        value = atoi(mask);
    };

    puntero = (int *) malloc(sizeof(int));
    *puntero = value;

    long posicion = posicion_cola(nuevo, (void *) puntero);

    if(posicion >= 0){
        printf("El elemento está en la posición %ld de la cola\n",posicion);
    }else{
        printf("Elemento no se encuentra en la cola\n");
    }

    free(puntero);

    unsigned long tam = tamano_cola(nuevo);

    if(destruir_cola(nuevo) < 0)
        fprintf(stderr,"Cola no pudo ser destruida, todavia tiene elementos\n");

    while(tam > 0){
        free(decolar(nuevo));
        tam = tamano_cola(nuevo);
    }
    printf("Elementos decolados\n");

    if(destruir_cola(nuevo) == 0)
        printf("Cola pudo ser destruida\n");
    

    return 0;
}