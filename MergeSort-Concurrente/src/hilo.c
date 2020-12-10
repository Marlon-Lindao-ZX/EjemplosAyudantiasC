#include "../include/general.h"

extern int tamano;
extern int *arreglo;
extern cola *merging_cola;

void* thread(void* arg) 
{ 
    data *info = (data *) arg;
    int low = info->low;
    int high = info->high;
  
    quickSort(low,high);

    return NULL;

} 

void merge_all(int niveles, unsigned long elementos){
    if(niveles > 0){
        if(elementos >= 2){
            data *info1 = (data *) decolar(merging_cola);
            data *info2 = (data *) decolar(merging_cola);
            int low = info1->low;
            int middle = info1->high;
            int end = info2->high;

            merge(low, middle, end);

            info1->low = low;
            info1->high = end;

            encolar(merging_cola,(void *) info1);
            free(info2);

            merge_all(niveles, elementos - 2);
            
        }else if(elementos == 1){

            data *temporal = (data *) decolar(merging_cola);
            encolar(merging_cola, (void *) temporal);
            merge_all(niveles, 0);

        }else if(elementos == 0){
            int nuevo_nivel = niveles -1;
            unsigned long tam = tamano_cola(merging_cola);
            merge_all(nuevo_nivel, tam);
        }
    }else if(niveles == 0){
        
        data *info1 = (data *) decolar(merging_cola);
        free(info1);
        destruir_cola(merging_cola);
    }

}