#include "../include/general.h"

int main(int argc, char **argv){

    int opt;

    int x;
    double y;
    char *string;

    bool pflag = false;

    while((opt = getopt(argc,argv, "i:d:s:p")) != -1){
        switch(opt){
            case 'i':
                x = atoi(optarg);
                int *puntero;
                if(x == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                printf("La representacion en hexadecimal de la variable tipo int cuyo valor es %d, es:\n", x);
                printhex((void *)&x, sizeof(int));
                puntero = &x;
                print_direccion_memoria((void *) &x, pflag, "int");
                print_direccion_memoria((void *) (&x + 2), pflag, "int");
                print_direccion_memoria((void *) (&x + 4) , pflag, "int");
                printf("%p\n",puntero);
                printf("%d-%p\n",*puntero++,puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", *++puntero,puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", ++*puntero,puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", *(++puntero),puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", ++(*puntero),puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", *(puntero++),puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", *(puntero)++,puntero);
                //++(*puntero) es equivalente a lo de arriba
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                puntero = &x;
                printf("%p\n",puntero);
                printf("%d-%p\n", (*puntero)++,puntero);
                printf("%d-%p\n",*puntero,puntero);
                printf("\n");
                break;
            case 'd':
                y = atof(optarg);
                if(y == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                printf("La representacion en hexadecimal de la variable tipo double cuyo valor es %lf, es:\n", y);
                printhex((void *)&y, sizeof(y));
                print_direccion_memoria((void *) &y, pflag, "double");
                print_direccion_memoria((void *) (&y + 2), pflag, "double");
                print_direccion_memoria((void *) (&y + 4), pflag, "double");
                break;

            case 's':
                string = optarg;
                printf("La representacion en hexadecimal del string cuyo valor es \"%s\", es:\n", string);
                printhex((void *)string, strlen(string));
                print_direccion_memoria((void *) string, pflag, "string");
                print_direccion_memoria((void *) (string + 2), pflag, "string");
                print_direccion_memoria((void *) (string + 4), pflag, "string");
                break;

            case 'p':
                pflag = true;
                break;
            
            case '?':
                printf("Opcion no reconocida\n");
                return -1;
            default:
                printf("Error de opcion\n");
                return -1;
        }
    }

    return 0;
}