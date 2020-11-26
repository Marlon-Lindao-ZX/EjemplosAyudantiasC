#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <errno.h>
#include <semaphore.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>

#define MAX 150
#define MAX2 1000000

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        fprintf(stderr, "Error de argumentos, tiene que usar de esta manera %s -n <num_veces>\n", argv[0]);
        exit(-1);
    }

    struct timeval beginning, end = {0};
    double promedio = 0;

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
            }else if (n <= 0){
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

    int p[2];

    if (pipe(p) < 0)
    {
        fprintf(stderr, "Error al llamar a la funcion pipe()\n");
        exit(1);
    }

    printf("Usando gettimeofday\n");

    for (int i = 0; i < n; i++)
    {

        gettimeofday(&beginning, NULL);
        pid_t pid = fork();
        if (pid > 0)
        {
            int status;
            if (waitpid(pid, &status, 0) > 0)
            {

                int readed;

                if ((readed = read(p[0], (void *)&end, sizeof(end))) < 0)
                {
                    fprintf(stderr, "Error al llamar a la funcion read()\n");
                    exit(-1);
                }
                double intervalo = (double)(end.tv_usec - beginning.tv_usec) / (double)1000000;
                intervalo += (double)((end.tv_sec - beginning.tv_sec));
                promedio += intervalo;
            }
            else
            {
                fprintf(stderr, "Error al llamar a la funcion waitpid()\n");
                exit(-1);
            }
        }
        else if (pid == 0)
        {
            int suma = 0;
            for (int i = 0; i < MAX2; i++)
            {
                suma += 10;
            }
            gettimeofday(&end, NULL);
            write(p[1], ((void *)&end), sizeof(end));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Error al llamar a la funcion fork()\n");
            exit(-1);
        }
    }

    promedio /= n;

    promedio *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API gettimeofday() es: %lf mili-segundos\n", promedio);

    clock_t start_t, start2_t, end_t = {0};

    double intervalo_t, promedio_clock = 0;

    printf("Usando clock\n");

    for (int i = 0; i < n; i++)
    {

        start_t = clock();
        pid_t pid = fork();
	start2_t = clock();
        if (pid > 0)
        {
            int status;
            if (waitpid(pid, &status, 0) > 0)
            {

                int readed;

                if ((readed = read(p[0], (void *)&end_t, sizeof(end_t))) < 0)
                {
                    fprintf(stderr, "Error al llamar a la funcion read()\n");
                    exit(-1);
                }

                intervalo_t = (double)((double)(start2_t - start_t) / (double) CLOCKS_PER_SEC);
                intervalo_t += (double) end_t/(double)CLOCKS_PER_SEC;
                promedio_clock += intervalo_t;
            }
            else
            {
                fprintf(stderr, "Error al llamar a la funcion waitpid()\n");
                exit(-1);
            }
        }
        else if (pid == 0)
        {
            int suma = 0;
            for (int i = 0; i < MAX2; i++)
            {
                suma += 10;
            }
            
            end_t = clock();
            write(p[1], ((void *)&end_t), sizeof(end_t));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Error al llamar a la funcion fork()\n");
            exit(-1);
        }
    }

    promedio_clock /= n;

    promedio_clock *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API clock() es: %lf mili-segundos\n", promedio_clock);

    
    promedio = 0;

    struct rusage usage;
    struct timeval beginning2;

    printf("Usando getrusage\n");

    for (int i = 0; i < n; i++)
    {

        getrusage(RUSAGE_SELF, &usage);
        beginning = usage.ru_utime;
        pid_t pid = fork();
        getrusage(RUSAGE_SELF, &usage);
        beginning2 = usage.ru_utime;
        if (pid > 0)
        {
            int status;
            if (waitpid(pid, &status, 0) > 0)
            {

                int readed;

                if ((readed = read(p[0], (void *)&end, sizeof(end))) < 0)
                {
                    fprintf(stderr, "Error al llamar a la funcion read()\n");
                    exit(-1);
                }
                double intervalo = (double)(end.tv_usec + beginning2.tv_usec - beginning.tv_usec) / (double)1000000;
                intervalo += (double)((end.tv_sec + beginning2.tv_sec - beginning.tv_sec));
                promedio += intervalo;
            }
            else
            {
                fprintf(stderr, "Error al llamar a la funcion waitpid()\n");
                exit(-1);
            }
        }
        else if (pid == 0)
        {
            int suma = 0;
            for (int i = 0; i < MAX2; i++)
            {
                suma += 10;
            }
            getrusage(RUSAGE_SELF, &usage);
            end = usage.ru_utime;
            write(p[1], ((void *)&end), sizeof(end));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Error al llamar a la funcion fork()\n");
            exit(-1);
        }
    }

    promedio /= n;

    promedio *= 1000;

    printf("Tiempo Promedio de proceso fork() calculado con API getrusage() es: %lf mili-segundos\n", promedio);

    
    exit(0);
}
