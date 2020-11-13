#include "general.h"


extern int f;

int z; // es una variable global no inicializada, va a ir en bss

int a = 0; // es una variable global inicializada, va a ir en data

int main(){

    struct timeval inicio,fin = {0};

    gettimeofday(&inicio,NULL);

    parameter p = {0};
    p.x = 20;
    p.y = -10;

    print_struct_puntero(&p);
    print_struct_copia(p);

    gettimeofday(&fin,NULL);

    printf("Tiempo inicial: \n");
    printf("Segundos: %ld\n", inicio.tv_sec);
    printf("Microsegundos: %ld\n", inicio.tv_usec);

    printf("Tiempo Final: \n");
    printf("Segundos: %ld\n", fin.tv_sec);
    printf("Microsegundos: %ld\n", fin.tv_usec);

    long intervalo = (fin.tv_sec - inicio.tv_sec)*1000000 + (fin.tv_usec - inicio.tv_usec);
    printf("Duracion de Ejecucion: %ld microsegundos\n",intervalo);

    printf("Extern: %d\n",f);

    /*
    malloc, calloc y realloc siempre me van un puntero y ese puntero es de tipo void *
    Que debo saber de malloc, calloc, y realloc
    malloc --> Separar memoria del Heap, pero no me inicializa los bytes a cero
    calloc --> Separa memoria, pero si inicializa los bytes a cero
    realloc --> Se usa para dismimuir o aumentar el espacio reservado

    Consideraciones:
    * Calloc es mas lento que malloc porque tiene que inicializar los bytes a cero.
    * Malloc como no inicializa los bytes, nosotros primero tenemos que asignar valores a las 
    * casillas antes de usarla(eso quiere decir que antes de leer un valor en ese espacio, debio
    * haber sido inicializado antes)
    */

    /*
    LA funcion malloc solo va a recibir un parametro que es la cantidad de bytes a separar
    Entonces para separar voy a necesitar multiplicar la cantidad de casillas que yo deseo
    (si lo vemos como arreglo la cantidad de casillas es la dimension del arreglo) por el tamaño
    de cada casilla(el tamaño de una posicion del arreglo)
    #bytes = cantidad casillas * tamaño de la casiila
    */
    gettimeofday(&inicio,NULL);
    int *puntero = (int *) malloc(40000000*sizeof(int));
    gettimeofday(&fin,NULL);
    intervalo = (fin.tv_sec - inicio.tv_sec)*1000000 + (fin.tv_usec - inicio.tv_usec);
    printf("Duracion de ejecucion de malloc: %ld microsegundos\n",intervalo);


    /*
    La funcion calloc en cambio va a recibir dos parametros:
    * la cantidad de casillas
    * el tamaño de la casilla
    
    Entonces calloc, es multiplicar cantidad casillas * tamaño de la casiila, para obtener el tamaño
    a separar, para despues ir byte por byte llenandolo con el valor de cero.

    entonces el pseudocodigo de calloc seria de esta manera

    calloc(cantidad_casillas,tamñao_casilla){
        void *puntero = malloc(cantidad_casillas * tamaño_casilla);

        for(int i= 0; i<(cantidad_casillas * tamaño_casilla);i++){
            *puntero = 0;
            puntero++;
        }
    }
    
    */
    gettimeofday(&inicio,NULL);
    int *puntero2 = (int *) calloc(400000000,sizeof(int));
    gettimeofday(&fin,NULL);
    intervalo = (fin.tv_sec - inicio.tv_sec)*1000000 + (fin.tv_usec - inicio.tv_usec);
    printf("Duracion de ejecucion de calloc: %ld microsegundos\n",intervalo);

    /*
    free() libera espacios de memoria reservados por malloc y calloc, esta funcion recibe un puntero a dicho espacio

    RECUERDE LIBERAR LO RESERVADO POR MALLOCC Y CALLOC ANTES DE TERMINAR EL PROGRAMA O SI SE HIZO LA RESERVA DENTRO DE UNA FUNCION, TIENE QUE LIBERAR
    ANTES DE QUE LA FUNCION TERMINE, PORQUE SI NO, SI EL PROGRAMA NO TIENE ACCESO AL PUNTERO DEFINIDO POR ESA FUNCION Y TIENE
    LA DIRECCION RETORNADA POR MALLOC O CALLOC, ENTONCES ESE ESPACIO DE MEMORIA RESERVADO NUNCA VA A PODER SER LIBERADO
    SI ESE ESPACIO DE MEMORIA YA NO PUEDE SER LIBERADO, ENTONCES MI PROGRAMA YA TIENE UNA FUGA DE MEMORIA.
    */
    free(puntero);
    free(puntero2);

    return 0;

}