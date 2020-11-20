#include "general.h"

int main(int argc, char **argv){

    int lineas = 10;

    char *filename = NULL;
    FILE *fp = NULL;

    if(argc < 2 || argc > 5 ){
        fprintf(stderr,"La cantidad de argumentos enviados, no es la adecuada\n");
        fprintf(stderr,"\nModo de Uso:\n");
        fprintf(stderr,"%s [-n <num_lineas>] <archivo_de_texto>\n",argv[0]);
        return -1;
    }

    manejar_opciones(argc,argv,&lineas,1);

    filename = argv[optind];

    if(filename == NULL){
        fprintf(stderr,"No se envio la ruta del archivo\n");
        fprintf(stderr,"\nModo de Uso:\n");
        fprintf(stderr,"%s [-n <num_lineas>] <archivo_de_texto>\n",argv[0]);
        return -1;
    }

    fp = fopen(filename,"r");

    leer_archivo(fp,lineas,1);

    fclose(fp);
    return 0;
}