#include "../include/general.h"

extern int *arreglo;

void merge(int low, int middle, int high) 
{ 
    int *left = NULL;
    int *right = NULL;

    int lenLeft = middle - low + 1;
    left = (int *) malloc(lenLeft*sizeof(int));

    int lenRight = high - middle;
    right = (int *) malloc(lenRight*sizeof(int));
  
    int i,j,k = 0;

    for (i = 0; i < lenLeft; i++) 
        left[i] = arreglo[i + low]; 
  
    for (j = 0; j < lenRight; j++) 
        right[j] = arreglo[j + middle + 1]; 
  
    k = low; 
    i = 0; 
    j = 0;

    while (i < lenLeft && j < lenRight) { 
        if (left[i] <= right[j]) 
            arreglo[k++] = left[i++]; 
        else
            arreglo[k++] = right[j++]; 
    } 

    while (i < lenLeft) { 
        arreglo[k++] = left[i++]; 
    } 
  
    while (j < lenRight) { 
        arreglo[k++] = right[j++]; 
    }

    if(left != NULL)
        free(left);
    
    if(right != NULL)
        free(right); 
}

void changePos(int *a, int*b){
    int temporal = *a; 
    *a = *b; 
    *b = temporal; 
}

int partition (int low, int high) 
{ 
    int pivot = arreglo[high];    
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arreglo[j] < pivot) 
        { 
            i++;
            changePos(&arreglo[i], &arreglo[j]); 
        } 
    } 
    changePos(&arreglo[i + 1], &arreglo[high]); 
    return (i + 1); 
} 
  

void quickSort(int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(low, high); 
 
        quickSort(low, pi - 1); 
        quickSort(pi + 1, high); 
    } 
} 