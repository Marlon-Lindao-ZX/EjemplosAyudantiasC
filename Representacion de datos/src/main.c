#include "../include/general.h"

int main(int argc, char **argv){

    int opt;

    int x;
    double y;
    char *string;

    while((opt = getopt(argc,argv, "i:d:s:")) != -1){
        switch(opt){
            case 'i':
                x = atoi(optarg);
                if(x == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                printf("La representacion en hexadecimal de la variable tipo int cuyo valor es %d, es:\n", x);
                printhex((void *)&x, sizeof(int));
                break;
            case 'd':
                y = atof(optarg);
                if(y == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                printf("La representacion en hexadecimal de la variable tipo double cuyo valor es %lf, es:\n", y);
                printhex((void *)&y, sizeof(y));
                break;

            case 's':
                string = optarg;
                printf("La representacion en hexadecimal del string cuyo valor es \"%s\", es:\n", string);
                printhex((void *)string, strlen(string));
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