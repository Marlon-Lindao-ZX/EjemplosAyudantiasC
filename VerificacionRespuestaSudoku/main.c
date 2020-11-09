#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define MAX 9

typedef struct
{
    int row;
    int column;
    int posicion;
} parameters;

void *worker_thread_row(void *parameter);
void *worker_thread_column(void *parameter);
void *worker_thread_square(void *parameter);
void print_sudoku();

/*
Ejemplo valido -- Es el sudoku puesto en el documento
{   {6,2,4,5,3,9,1,8,7},
    {5,1,9,7,2,8,6,3,4},
    {8,3,7,6,1,4,2,9,5},
    {1,4,3,8,6,5,7,2,9},
    {9,5,8,2,4,7,3,6,1},
    {7,6,2,3,9,1,4,5,8},
    {3,7,1,9,5,6,8,4,2},
    {4,9,6,1,8,2,5,7,3},
    {2,8,5,4,7,3,9,1,6}  };
*/

char sudoku[MAX][MAX] = 
    {   {6,2,4,5,3,9,1,8,7},
        {5,1,9,7,2,8,6,3,4},
        {8,3,7,6,1,4,2,9,5},
        {1,4,3,8,6,5,7,2,9},
        {9,5,8,2,4,7,3,6,1},
        {7,6,2,3,9,1,4,5,8},
        {3,7,1,9,5,6,8,4,2},
        {4,9,6,1,8,2,5,7,3},
        {2,8,5,4,7,3,9,1,6}  };
char validadores[MAX*3] = {0};


int main(){
    pthread_t hilos[MAX*3];

    char posiciones[MAX][2] = {{0,0},{3,0},{6,0},{0,3},{3,3},{6,3},{0,6},{3,6},{6,6}};

    parameters *parametro = NULL;

    char flag = 1;

    print_sudoku();

    for(int i=0;i<MAX;i++){
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = i;
        parametro->column = 0;
        parametro->posicion = i;
		pthread_create(&hilos[i],NULL,worker_thread_row,(void *) parametro);
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = 0;
        parametro->column = i;
        parametro->posicion = i + 9;
        pthread_create(&hilos[i+9],NULL,worker_thread_column,(void *) parametro);
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = posiciones[i][0];
        parametro->column = posiciones[i][1];
        parametro->posicion = i + 18;
        pthread_create(&hilos[i+18],NULL,worker_thread_square,(void *) parametro);
    }

    for(int i = 0; i<MAX*3; i++){
        pthread_join(hilos[i],NULL);
        flag &= validadores[i];    
    }

    if(flag)
        printf("Solucion de Sudoku es valida\n");
    else
        printf("Solucion de Sudoku es invalida\n");
    
    return 0;
}

void *worker_thread_row(void *parameter){
    parameters *parametro = (parameters *) parameter;
    char checker[MAX] = {0};
    char flag = 1;
    char pos = -1;

    for(int i=0;i<MAX;i++){
        pos = (sudoku[parametro->row][i]) - 1;
        if(!checker[pos])
            checker[pos] = 1;
        else
            flag = 0;
    }

    if(flag)
        validadores[parametro->posicion] = 1;
    
    free(parametro);
    return NULL;   
}

void *worker_thread_column(void *parameter){
    parameters *parametro = (parameters *) parameter;
    char checker[MAX] = {0};
    char flag = 1;
    char pos = -1;
    
    for(int i=0;i<MAX;i++){
        pos = (sudoku[i][parametro->column]) -1;
        if(!checker[pos])
            checker[pos] = 1;
        else 
            flag = 0;
        
    }

    if(flag)
        validadores[parametro->posicion] = 1;
    
    free(parametro);
    return NULL;
}

void *worker_thread_square(void *parameter){
    parameters *parametro = (parameters *) parameter;
    char checker[MAX] = {0};
    char flag = 1;
    char pos = -1;

    for(int i=parametro->row;i<(parametro->row) + 3;i++){
        for(int j=parametro->column;j<(parametro->column) + 3;j++){
            pos = (sudoku[i][j]) - 1; 
            if(!checker[pos])
                checker[pos] = 1;
            else 
                flag = 0;
        }
    }

    if(flag)
        validadores[parametro->posicion] = 1;
    

    free(parametro);
    return NULL;
}

void print_sudoku(){

    printf("Imprimiendo Sudoku:\n");

    for(int i=0;i<MAX;i++){
        printf("-------------------\n");
        printf("|");

        for(int j=0;j<MAX;j++)
            printf("%d|",sudoku[i][j]);
        
        printf("\n");
    }
    printf("-------------------\n");
}