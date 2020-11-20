#include "general.h"

int main(int argc, char ** argv){

    int opt;

    int n;
    int x;
    int y;

    while((opt = getopt(argc,argv,"n:x:y:")) != -1){
        switch(opt){
            case 'n':
                    n = atoi(optarg);
                    if(n == 0 && strcmp(optarg,"0") != 0){
                        fprintf(stderr,"Lo ingresado no es un numero\n");
                        exit(-1);
                    }
                    break;
            
            case 'x':
                    x = atoi(optarg);
                    if(x == 0 && strcmp(optarg,"0") != 0){
                        fprintf(stderr,"Lo ingresado no es un numero\n");
                        exit(-1);
                    }
                    break;
            case 'y':
                    y = atoi(optarg);
                    if(y == 0 && strcmp(optarg,"0") != 0){
                        fprintf(stderr,"Lo ingresado no es un numero\n");
                        exit(-1);
                    }
                    break;
            case '?':
            default:
                    fprintf(stderr,"Opcion invalida\n");
                    exit(-1);
        }
    }

    coord_t *coords = (coord_t *) malloc(n * sizeof(coord_t));

    for(int i=0; i<n;i++){
        coords[i].x = x*i;
        coords[i].y = y*i*2;
    }

    for(int i=0; i<n;i++){
        printf("Imprimiendo las coordenadas de la posicion %d del arreglo: \n",i);
        printf("X: %d\n", coords[i].x);
        printf("Y: %d\n", coords[i].y);
        printf("\n\n");
    }

    free(coords);
    return 0;
    
}