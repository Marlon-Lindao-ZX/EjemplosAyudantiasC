#include "general.h"

int main(int argc, char **argv){
    /*
    int x = 35657;
    
    char *z = &x;
    int *v = &x;

    printf("El valor de la direccion: %d\n", *z);
    printf("El valor de la direccion: %d\n", *v);
    */
   //Imprimo la cantidad de argumentos enviado al momento de la ejecucion
    printf("Contador de argumentos: %d\n", argc);

    //Imprimo el listado de los argumentos enviado al programa
    for(int i=0; i<argc; i++){
        printf("Iteracion %d\n", i);
        /*
        printf("%p\n",argv);
        printf("%p\n",(argv + i));
        */
         printf("Argumento %d es: %s\n",i,*(argv + i));
        //printf("Argumento %d es: %s\n",i,argv[i]); --> Otra forma de hacer la linea de arriba
    }
    
    //Variable usada para el manejo de opciones
    int opt;
    int num_opcion_l;

    //Recoge todas las opciones que encuentre en el listado de argumentos
    //getopt solo reconoce las opciones definido en la cadena de texto
    //Conocer que getopt particiona el string de tal forma, que toma cada caracter como una
    //opcion diferente.
    //case '?' captura aquellas opciones no reconocidas por opt
    //default es para aquellas opciones definidas en el string pero que no se ha implementado su case
    while((opt = getopt(argc,argv, "l:hoa")) != -1){
        switch(opt){
            case 'h':
                printf("Entraste a la opcion h\n");
                break;
            
            case 'o':
                printf("Entraste a la opcion o\n");
                break;
            
            case 'l':
                printf("Entraste a la opcion l y su argumento es: %s\n",optarg);
                num_opcion_l = atoi(optarg);
                if(num_opcion_l == 0 && strcmp(optarg,"0") != 0){
                    printf("Opcion l recibe un argumento numerico\n");
                    return -1;
                }
                printf("El valor numerico del argumento de l es: %d\n", num_opcion_l);
                break;
            case 'a':
                printf("Entraste a la opcion a\n");
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