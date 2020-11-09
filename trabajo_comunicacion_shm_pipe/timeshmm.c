#include "general.h"

int main(int argc, char **argv){

    if(argc == 1){
        fprintf(stderr,"Este programa necesita mas argumentos para su ejecucion\n");
        exit(-1);
    }


	char *name = argv[1];
	int cantidad = argc - 1;
 	/*
    El puntero argv2 es usado como contenedor para el nombre del comando enviado y sus argumentos
    */
    char **argv2 = (char **) malloc(cantidad * sizeof(char *));
    
    /*
    La estructura timeval es usada por las funciones definidas en la libreria sys/time.h para guardar
    el resultado de los tiempos, por ejemplo la funcion gettimeofday(), aqui se guardan los segundos, microsegundos que
    retornen dichas funciones.
    Los campos que se usan aqui es:
    t_sec --> Representa los segundos, y es de tipo time_t
    t_usec --> Representa los microsegundos, y es de tipo suseconds_t
    Para imprimir los campos se puede usar %ld en la cadena de texto
    En un sentido ambos valores son numeros enteros grandes(mas o menos como long, ya que se 
    puede imprimir por consola usando %ld)
    Mas info, revisar:
    https://pubs.opengroup.org/onlinepubs/007908775/xsh/systime.h.html
    */
    struct timeval beginning,end = {0};
	
	int contador = 0;

	while(contador < cantidad){
		argv2[contador] = argv[1 + contador];
        contador++;
    }

    /*
    La memoria compartida en cierto punto se lo puede ver como un espacio que el kernel separa
    donde se puede escribir o leer (Tecnicamente es una pagina donde se pueden mapear datos), y que cualquier proceso puede acceder a ello, con solo conocer
    el nombre del espacio. --> Ojo: estos espacios necesitan un nombre para ser identificados.
    De alguna manera se lo puede ver como malloc, solo que la diferencia radica que la separacion
    de espacio es en alguna seccion de la memoria del sistema, y no en el Heap del contexto del proceso
    como sucede con malloc y calloc.
    Este proceso de memoria compartida sirve mucho para poder realizar comunicacion entre procesos diferentes.
    Por ejemplo, puede ser usado para la comuncacion entre el proceso timeshmm y timepipe
    La desventaja es que es un proceso engorroso para crear la memoria, ademas de que hay que 
    saber mover bien el puntero para que no de segmentation fault.
    */
    //Tamaño de la memoria compartida en bytes
    const int size = 4096; 
    //Memoria compartida necesita un nombre
    const char* memory_name = "TIME";
    /*
    Es como un descriptor de archivo, con el puedo acceder a la seccion de la memoria, y pedir
    un puntero para poder leer o escribir en ese espacio.
    */
    int shm_fd;
    /*
    Es el puntero hacia la memoria compartida, con el puedo guardar o leer valores de forma directa
    hacia esa seccion de la memoria.
    */
    void* ptr;  
	
    //Se crean dos procesos, donde el hijo es el que hara uso de excevp para ejecutar el comando de bash o ejecutable enviado
	pid_t pid = fork();
	if(pid > 0){
		/*
        El padre espera a que el hijo termine, y pueda proceder a realizar el calculo del intervalo de tiempo   
        Cuando el hijo termine, el padre leera la memoria compartida para ver lo que el hijo escribio.
        En el padre, no es necesario separar memoria, porque el padre va a leer contenido de la memoria
        */
        int status;
		if( waitpid(pid,&status,0) > 0 ) {
            /*
            Esta funcion hace un requerimiento al reloj interno del sistema para conocer el tiempo actual
            Y necesita un puntero a una estructura timeval para guardar la informacion
            */
            gettimeofday(&end,NULL);
            /*
            Se lo puede ver como la funcion open para las memorias compartidas, aqui se hace
            un requerimiento al kernel para que cree un identificador para la memoria memoria compartida, 
            por ello se puede ver que se usa las mascaras usadas en la funcion open(), ademas de los permisos.
            Es como si ese espacio estuviese siendo tratado como un archivo, mostrandonos la particularidad 
            de Linux que trata a todo como archivo
            Esta funcion va a buscar la memoria que tenga el nombre enviado.
            Ojo: para tener la comunicacion entre procesos, en ambos procesos se debe tener el mismo nombre en el open.
            */
            shm_fd = shm_open(memory_name, O_RDONLY, 0666);
            /*
            La funcion mmap es la que me da el puntero para poder leer o escribir en la memoria compartida
            -> 1er argumento: Es la direccion de memoria donde queremos que el kernel cree la memoria compartida
            si es 0 o NULL, el kernel buscara donde crear la memoria
            
            -> 2do argumento: El tamaño de la memoria compartida
            
            -> 3er argumento: La accion sobre la memoria compartida
            En este caso, el padre usa PROT_READ para poder usar el puntero para leer datos de la memoria compartida
            
            -> 4to argumento: La bandera para la memoria compartida, con MAP_SHARED se le dice al kernel, que esta memoria puede ser accedida por otros procesos
            
            -> 5to argumento: El descriptor o identificador para la memoria compartida. 
            
            -> ultimo argumento: El offset para poder llenar la memoria compartida, se lo puede ver como
            decirle desde yo quiero leer o escribir de la memoria compartida, en este caso, con 0 
            estoy en el principio de la memoria.
            
            Como se ve, el ptr es un puntero hacia el contenido de la memoria, y con el puedo
            escribir o leer informacion
            */
            ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);
            /*
            Como ptr es un puntero a void, puedo hacer un casting hacia otro tipo de dato para acceder a su valor
            En este caso, el hijo ha escrito en la memoria el contenido de la estructura timeval con su informacion de tiempo de inicio
            */
            beginning = *((struct timeval *) ptr);
            //Calculo para obtener el intervalo de tiempo
            double intervalo = (double) (end.tv_usec - beginning.tv_usec)/(double) 1000000;
		    printf("Tiempo Transcurrido: %lf segundos\n",intervalo);
            //Se lo puede ver como close, que cierra el archivo, aqui se cierra el acceso a la memoria compartida.
            shm_unlink(memory_name); 
        } else {
            fprintf(stderr,"Error al llamar a la funcion waitpid()\n");
            exit(-1);
        }      
	} else if(pid == 0 ){
        /*
        El hijo realiza la accion de escribir en la memoria compartida el tiempo que inicia el llamado a execvp
        Ademas ejecuta la funcion execvp
        */

        /*
        Basicamente ocurre lo mismo que en el padre, solo que el open aqui recibe las banderas para poder
        crear la memoria compartida si no existe, ademas de permiso de escritura, entonces aqui es donde se crea la memoria compartida, pero el kernel todavia no sabe donde ubicarla
        */
        shm_fd = shm_open(memory_name, O_CREAT | O_RDWR, 0666);
        /*
        Con esta funcion se le da el tamaño a la memoria compartida, es decir se separa memoria
        Inicialmente la memoria compartida tiene un tamaño de 0 bytes
        */ 
        ftruncate(shm_fd, size);
        /*
        Es la misma explicacion que el padre, lo unico que cambia es el tercer argumento, donde
        la mascara PROT_WRITE es usado para poder escribir en la memoria compartida, con el puntero que me
        retorna mmap.
        */
        ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        gettimeofday(&beginning,NULL);
        /*
        Uso el puntero para guardar el contenido del struct timeval beginning en la memoria compartida
        Se hace un casting al ptr porque recordar que es un puntero tipo void
        */
        *((struct timeval *) ptr) = beginning;
        /*
        Desplazo el puntero segun el tamaño de la estructura timeval
        */
        ptr += sizeof(beginning);
        //Uso execvp para ejecutar el comando enviado.
		execvp(name,argv2);
		fprintf(stderr,"Error al llamar a la funcion execvp()\n");
		exit(-1);
	} else {
		fprintf(stderr,"Error al llamar a la funcion fork()\n");
        exit(-1);
	}

	free(argv2);
	exit(0);

}