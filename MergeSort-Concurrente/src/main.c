#include "../include/general.h"

int *arreglo = NULL;
int *resultado[NP] = {0};
int tamano = 0;
cola *merging_cola;

int main(int argc, char **argv){

    char *archivo = NULL;
    FILE *fp = NULL;
    bool mode = true;

    manejar_opciones(argc,argv,&archivo);

    if(archivo != NULL)
    {
        if(!validate_file_name(archivo))
            end_with_error("Archivo csv no valido\n");
        else
            fp = abrir_archivo(archivo);

        mode = false;
    }
    else
    {
        fp = stdin;
        mode = true;        
    }

    readAndWrite(fp,mode);

    int niveles = exponente_2(NP);

    merging_cola = crear_cola();

    pthread_t hilos[NP] = {0};

    for (int i = 0; i < NP; i++){
        
        data* info = (data *) malloc(sizeof(data));
        info->low = i * (tamano/NP);
        if(i == NP -1)
            info->high = tamano - 1;
        else
            info->high = ((i + 1) * (tamano/NP)) - 1;
        info->nivel = niveles;
        info->posicion = i;
        encolar(merging_cola,(void *) info);
        
        pthread_create(&hilos[i], NULL, thread, (void*) info); 
    }

    for (int i = 0; i < NP; i++) 
        pthread_join(hilos[i], NULL);

    merge_all(niveles,NP);  
    
    for(int i = 0; i<tamano; i++)
        printf("%d: %d\n",i,arreglo[i]);
    
    if(archivo != NULL)
        fclose(fp);
    
    free(arreglo);
    
    
   return 0;
}