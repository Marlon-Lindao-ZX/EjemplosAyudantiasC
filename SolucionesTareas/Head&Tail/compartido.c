#include "general.h"

void print_help(char *programa, int mode){
    
    if(mode == 1){
        printf("El %s es un programa que imprime las primeras lineas de un archivo de texto/n",programa);
    } else if(mode == 2){
        printf("El %s es un programa que imprime las ultimas lineas de un archivo de texto/n",programa);
    }
    printf("\nModo de Uso:\n");
    printf("%s [-n <num_lineas>] <archivo_de_texto>\n",programa);
    printf("\nArgumentos:\n\n");
    printf(" h\t\tAyuda, muestra este mensaje\n");
    if(mode == 1){
        printf(" n <num_lineas>\tImprime las num_lineas primeras lineas deñ archivo, si es omitido, imprime las 10 primeras lineas\n");
    } else if(mode == 2){
        printf(" n <num_lineas>\tImprime las num_lineas ultimas lineas deñ archivo, si es omitido, imprime las 10 ultimas lineas\n");
    }
}

void manejar_opciones(int argc, char **argv, int *lineas, int mode){

    int opt;

    while((opt = getopt(argc,argv,"n:h")) != -1){
        switch(opt){
            case 'n':
                    *lineas = atoi(optarg);
                    if(*lineas == 0 && strcmp(optarg,"0") != 0){
                        fprintf(stderr,"Lo ingresado no es un numero\n");
                        exit(-1);
                    }
                    if(*lineas <= 0){
                        fprintf(stderr,"El numero ingresado es negativo o cero\n");
                        exit(-1);
                    }
                    break;
            case 'h':
                    print_help(argv[0],mode);
                    exit(0);
            case '?':
            default:
                    fprintf(stderr,"Opcion invalida\n");
                    exit(-1);
        }
    }

}


void leer_archivo(FILE *fp, int lineas, int mode){

    char buffer[MAX] = {0};
    char *mask = buffer;
    size_t size = MAX;
    size_t l = 0;

    int saltoLinea = 0;

    if (mode == 2)
    {

        int temp = lineas;
        int acumulador = 0;

        //Este for recorre hasta encontrar todas las ultimas lineas
        for (int i = 2; temp; i++)
        {
            //fseek va a desplazar el puntero interno del archivo, 1 byte antes del final del archivo
            if (fseek(fp, -i, SEEK_END) == -1)
            {
                printf("Error going to the end of the file\n");
                exit(-1);
            }
            //cogo el byte en la posicion actual
            saltoLinea = fgetc(fp);
            if (saltoLinea == '\n')
            {
                getline(&mask, &size, fp);
                acumulador += strlen(mask);
                memset(mask, 0, MAX);
                temp--;
            }
        }
        if (fseek(fp, -acumulador, SEEK_END) == -1)
        {
            printf("Error going to the end of the file\n");
            exit(-1);
        }
    }

    while((l=getline(&mask,&size,fp)) != -1){
        
        printf("%s",mask);
        memset(mask,0,MAX);

        if(lineas > 0){
            lineas--;
        }

        if(lineas == 0)
            break;
    
    }

}
