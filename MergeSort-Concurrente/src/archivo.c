#include "../include/general.h"

extern int* arreglo;
extern int tamano;

bool validate_file_name(char *archivo){
    regex_t regex;

    char extension[4] = {'.','c','s','v'};

    int tam = strlen(archivo);

    bool result = true;

    for(int i=0; i<4;i++)
        result &= extension[i] == archivo[tam -4 + i];

    return result;
}

FILE * abrir_archivo(char *archivo){
    FILE *fp = fopen(archivo,"r+");
    if(fp == NULL)
        end_with_error("No se pudo abrir el archivo\n");
    return fp;
}


void readAndWrite(FILE *fp, bool mode){

    char buffer[SIZE];
    char *buffer2 = NULL;

    size_t line = 0;
    size_t tam = SIZE;

    cola *mi_cola = crear_cola();

    int *elemento = NULL;
    int conversion = 0;

    if(mode)
        printf("Ingrese el arreglo numerico separado por comas: ");
    else
        getline(&buffer2, &tam, fp);
    
    memset(buffer, 0, SIZE);

    while (fgets(buffer, SIZE, fp) != NULL)
    {
        char *tmp = strtok(buffer,",");
        while(tmp != NULL){
            if(cambiar_string_a_int(tmp,&conversion)){
                elemento = (int *) malloc(sizeof(int));
                *elemento = conversion;
                encolar(mi_cola,(void *) elemento);
            }
            tmp = strtok(NULL,",");
        }
        memset(buffer, 0, SIZE);
        if(mode) break;
        
    }

    unsigned long tam2 = tamano_cola(mi_cola);

    arreglo = (int *) malloc(tam2 * sizeof(int));

    int i = 0;

    while(tam2 > 0){
        elemento = (int *) decolar(mi_cola);
        arreglo[i++] = *elemento;
        free((void *) elemento);
        tam2 = tamano_cola(mi_cola);
    }

    tamano = i;

    destruir_cola(mi_cola);
    
}