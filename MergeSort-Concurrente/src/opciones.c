#include "../include/general.h"

void manejar_opciones(int argc, char **argv, char **archivo){

    int opt;

    while((opt = getopt(argc,argv,"f:h")) != -1){
        switch(opt){
            case 'f':
                    *archivo = optarg;
                    break;
            case 'h':
                    print_help(argv[0]);
                    exit(0);
            case '?':
            default:
                    print_error("Opcion invalida\n");
                    exit(-1);
        }
    }

}

void print_help(char *programa){
    printf("El %s es un programa que ordena una lista de numeros usando el algoritmo mergesort/n",programa);
    printf("\nModo de Uso:\n");
    printf("%s [-f <ruta_archivo_csv>]\n",programa);
    printf("\nArgumentos:\n\n");
    printf(" h\t\tAyuda, muestra este mensaje\n");
    printf(" f <ruta_archivo_csv>\tObtiene la lista de numeros del archivo csv enviado, si es omitido, el programa le pide los datos de la lista por teclado\n");
}