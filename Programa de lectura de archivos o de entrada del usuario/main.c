#include "general.h"

int main(int argc, char **argv){
    
    int opt;
    char *file = NULL;
    int cantidad_lineas = -1;
    FILE *archivo = NULL;
    char buffer[MAX];
    char *mask = buffer;
    size_t size = MAX;
    size_t l;

    
    while((opt = getopt(argc,argv, "f:n:")) != -1){
        switch(opt){
            case 'f':
                file = optarg;
                break;

            case 'n':
                cantidad_lineas = atoi(optarg);
                if(cantidad_lineas == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                if(cantidad_lineas <= 0)
                    cantidad_lineas = -1;

                break;
            
            case '?':
                printf("Opcion no reconocida\n");
                return -1;
            default:
                printf("Error de opcion\n");
                return -1;
        }
    }

    if(file == NULL)
        archivo = stdin;
    else
        archivo = fopen(file,"r");
    

    if(archivo == NULL){
        printf("El archivo %s no pudo ser abierto\n", file);
        return -1;
    }

    if(file == NULL)
        printf(">>");
    
    //Para controlar el getline, esta funcion retorna -1 cuando ya no tiene nada mas que leer
    while((l=getline(&mask,&size,archivo)) != -1){
        
        printf("%s",mask);
        memset(mask,0,MAX);
        if(file == NULL)
            printf(">>");

        if(cantidad_lineas > 0){
            cantidad_lineas--;
        }

        if(cantidad_lineas == 0)
            break;
    
    }

    printf("\n");

    if(file != NULL)
        fclose(archivo);

    return 0;
}