#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX2 1024

struct timeval *beginnings;
struct timeval *beginnings2;
struct timeval *beginnings3;
struct timeval *ends;
struct timeval *ends2;

clock_t *beginnings_t;
clock_t *beginnings2_t;
clock_t *ends_t;

void tarea()
{
    int suma = 0;
    for (int i = 0; i < MAX2; i++)
    {
        suma += 10;
    }
}

void *worker_thread_api1(void *parametro){
    int *posicion = (int *) parametro;
    tarea();
    struct timeval end = {0};
    gettimeofday(&end, NULL);
    ends[*posicion] = end;
    free(posicion);
    return NULL;
}

void *worker_thread_api2(void *parametro){
    int *posicion = (int *) parametro;
    tarea();
    ends_t[*posicion] = clock();
    free(posicion);
    return NULL;
}

void *worker_thread_api3(void *parametro){
    int *posicion = (int *) parametro;
    tarea();
    struct rusage usage = {0};
    getrusage(RUSAGE_SELF, &usage);
    ends2[*posicion] = usage.ru_utime;
    free(posicion);
    return NULL;
}

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        fprintf(stderr, "Error de argumentos, tiene que usar de esta manera %s -n <num_veces>\n", argv[0]);
        exit(-1);
    }

    int opt;

    int n, contador = 0;

    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            if (n == 0 && strcmp(optarg, "0") != 0)
            {
                printf("Opcion n recibe un argumento numerico\n");
                return -1;
            }
            else if (n <= 0)
            {
                printf("Opcion n debe ser un valor entero positivo\n");
                return -1;
            }
            break;
        case '?':
            printf("Opcion no reconocida\n");
            return -1;
        default:
            printf("Error de opcion\n");
            return -1;
        }
    }

    pthread_t *threads = (pthread_t *) malloc(n*sizeof(pthread_t));

    beginnings = (struct timeval *) malloc(n*sizeof(struct timeval));
    ends = (struct timeval *) malloc(n*sizeof(struct timeval));

    beginnings_t = (clock_t *) malloc(n*sizeof(clock_t));
    beginnings2_t = (clock_t *) malloc(n*sizeof(clock_t));
    ends_t = (clock_t *) malloc(n*sizeof(clock_t));
    
    beginnings2 = (struct timeval *) malloc(n*sizeof(struct timeval));
    beginnings3 = (struct timeval *) malloc(n*sizeof(struct timeval));
    ends2 = (struct timeval *) malloc(n*sizeof(struct timeval));

    printf("Usando gettimeofday\n");

    double promedio = 0;

    for(int i=0; i<n; i++){
        int *posicion = (int *) malloc(sizeof(int));
        *posicion = i;
        struct timeval beginning = {0};
        gettimeofday(&beginning, NULL);
        beginnings[i] = beginning;
        pthread_create(&threads[i],NULL,worker_thread_api1,(void *) posicion);
    }

    for(int i=0; i<n; i++){
        pthread_join(threads[i],NULL);
        double intervalo = (double)(ends[i].tv_usec - beginnings[i].tv_usec) / (double)1000000;
        intervalo += (double) (ends[i].tv_sec - beginnings[i].tv_sec);
        promedio += intervalo;
    }

    promedio /= n;
    promedio *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API gettimeofday() es: %lf mili-segundos\n", promedio);
    
    free(beginnings);
    free(ends);

    printf("Usando clock\n");
    
    promedio = 0;

    for(int i=0; i<n; i++){
        int *posicion = (int *) malloc(sizeof(int));
        *posicion = i;
        beginnings_t[i] = clock();
        pthread_create(&threads[i],NULL,worker_thread_api2,(void *) posicion);
        beginnings2_t[i] = clock();
    }

    for(int i=0; i<n; i++){
        pthread_join(threads[i],NULL);
        double intervalo = (double)(beginnings2_t[i] - beginnings_t[i]) / (double) CLOCKS_PER_SEC;
        intervalo += (double)(ends_t[i])/ (double) CLOCKS_PER_SEC;
        promedio += intervalo;
    }

    promedio /= n;
    promedio *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API clock() es: %lf mili-segundos\n", promedio);
    free(beginnings_t);
    free(beginnings2_t);
    free(ends_t);

    printf("Usando getrusage\n");
    
    promedio = 0;
    struct rusage usage = {0};
    
    for(int i=0; i<n; i++){
        int *posicion = (int *) malloc(sizeof(int));
        *posicion = i;
        getrusage(RUSAGE_SELF, &usage);
        beginnings2[i] = usage.ru_utime;
        pthread_create(&threads[i],NULL,worker_thread_api3,(void *) posicion);
        getrusage(RUSAGE_SELF, &usage);
        beginnings3[i] = usage.ru_utime;
    }

    for(int i=0; i<n; i++){
        pthread_join(threads[i],NULL);
        double intervalo = (double)(ends2[i].tv_usec - beginnings2[i].tv_usec) / (double)1000000;
        intervalo += (double) (ends2[i].tv_sec - beginnings2[i].tv_sec);
        promedio += intervalo;
    }

    promedio /= n;
    promedio *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API getrusage() es: %lf mili-segundos\n", promedio);
    free(beginnings2);
    free(beginnings3);
    free(ends2);
    free(threads);
}
