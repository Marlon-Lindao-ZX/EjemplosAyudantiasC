#include "general.h"

int main(int argc, char **argv){

    /*
    La explicacion de este programa, como la estructura timeval ya esta en timeshmm.c
    Aqui solo estara la explicacion del pipe
    */

	if(argc == 1){
        fprintf(stderr,"Este programa necesita mas argumentos para su ejecucion\n");
        exit(-1);
    }


	char *name = argv[1];
	int cantidad = argc - 1;
 	char **argv2 = (char **) malloc(cantidad * sizeof(char *));
    struct timeval beginning,end = {0};

    /*
    Un pipe es el medio de comunicacion entre dos procesos, se lo puede ver como un archivo 
    especial para este fin.
    En palabras tecnicas, el pipe sirve para que la salida estandar(stdout)) de un proceso, se vuelve
    en la entrada estandar del otro(stdin)
    Por eso, estos procesos para acceder al pipe, necesitaran un descriptor de archivo para escribir
    y otro para leer.
    La ventaja que tiene esta metodologia es que solo se necesita usar descriptores para la 
    comunicacion, y no el proceso que toca hacer con la memoria compartida.
    La desventaja es que solo puede ser usado por un programa que haga el uso de fork() y que
    use esta via para comunicarse con sus procesos hijos
    Es decir, con pipe no puedo comunicar el proceso timepipe con timeshmm, sino que timepipe solo
    puede usar el pipe para comunicarse con sus hijos
    */
    int p[2];
	
	int contador = 0;

	while(contador < cantidad){
		argv2[contador] = argv[1 + contador];
        contador++;
    }

    /*
    La funcion pipe() creara el canal de comunicacion, y necesitara un arreglo de enteros de diemension 2
    (int arreglo[2]), como resultado en arreglo[0] estara el descriptor para leer el pipe y 
    en arreglo[1] estara el descriptor para escribir en el pipe
    Si la funcion pipe() falla, retorna un -1
    */
    if(pipe(p) < 0){
        fprintf(stderr,"Error al llamar a la funcion pipe()\n");
        exit(1);
    }

	pid_t pid = fork();
	if(pid > 0){
		int status;
		if( waitpid(pid,&status,0) > 0 ) {
            int readed;
            gettimeofday(&end,NULL);
            /*
            El padre lee el contenido que el hijo ha escrito, y como tengo el descriptor del pipe para leer
            Puedo usar read para leer lo que se haya escrito
            En este caso, en read envio la estructura beginning directamente para que se guarde los bytes
            enviados por el hijo, ya que asi mismo, el hijo uso write para escribir los bytes de esa 
            estructura.
            */
            if((readed = read(p[0], (void *) &beginning, sizeof(beginning))) < 0){
                fprintf(stderr,"Error al llamar a la funcion read()\n");
                free(argv2);
                exit(-1);
            }
            double intervalo = (double) (end.tv_usec - beginning.tv_usec)/(double) 1000000;
		    printf("Tiempo Transcurrido: %lf segundos\n",intervalo);
        } else {
            fprintf(stderr,"Error al llamar a la funcion waitpid()\n");
            free(argv2);
            exit(-1);
        }
        
        
	} else if(pid == 0 ){
        gettimeofday(&beginning,NULL);
        /*
        Como la funcion pipe() me retorno el descriptor para escribir en el, puedo usar la funcion
        write(), para escribir bytes directamente en el pipe, por lo que se puede ver que al write
        estoy enviando la estructura timeval beginning, para que coja su contenido y lo ponga en el
        pipe, de esa manera el padre podra leer el contenido de dicha estructura, y con eso poder 
        hacer el calculo del intervalo de tiempo.
        */
        write(p[1],((void *) &beginning),sizeof(beginning));
		execvp(name,argv2);
		fprintf(stderr,"Error al llamar a la funcion execvp()\n");
        free(argv2);
		exit(-1);
	} else {
		fprintf(stderr,"Error al llamar a la funcion fork()\n");
        free(argv2);
        exit(-1);
	}

	free(argv2);
	exit(0);

}