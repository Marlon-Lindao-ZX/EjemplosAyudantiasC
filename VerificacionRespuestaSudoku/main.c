#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define MAX 9

/*
Estructura dada en el deber para que los hilos conozcan la posicion de la matriz donde debe
trabajar
Ademas se agrego una opcion mas para tener la posicion del arreglo char de validacion, de tal
manera, pueda colocar su resultado del analisis en dicha posicion con 0 o 1
*/
typedef struct
{
    int row;
    int column;
    int posicion;
} parameters;

/*
Esta es la funcion callback de un hilo que tiene que verificar una sola fila
*/
void *worker_thread_row(void *parameter);

/*
Esta es la funcion callback de un hilo que tiene que verificar una sola colummna
*/
void *worker_thread_column(void *parameter);

/*
Esta es la funcion callback de un hilo que tiene que verificar una minimatriz 3x3
*/
void *worker_thread_square(void *parameter);

/*
Imprime el sudoku de manera que puede ser apreciable al usuario
*/
void print_sudoku();

/*
Es el contendido de una respuesta valida de sudoku
Ejemplo valido -- Es el sudoku puesto en el documento
{   {6,2,4,5,3,9,1,8,7},
    {5,1,9,7,2,8,6,3,4},
    {8,3,7,6,1,4,2,9,5},
    {1,4,3,8,6,5,7,2,9},
    {9,5,8,2,4,7,3,6,1},
    {7,6,2,3,9,1,4,5,8},
    {3,7,1,9,5,6,8,4,2},
    {4,9,6,1,8,2,5,7,3},
    {2,8,5,4,7,3,9,1,6}  };
    
Ademas la variable sudoku, es la matriz global que los hilos van a poder acceder para realizar
su analisis
*/
char sudoku[MAX][MAX] = 
    {   {6,2,4,5,3,9,1,8,7},
        {5,1,9,7,2,8,6,3,4},
        {8,3,7,6,1,4,2,9,5},
        {1,4,3,8,6,5,7,2,9},
        {9,5,8,2,4,7,3,6,1},
        {7,6,2,3,9,1,4,5,8},
        {3,7,1,9,5,6,8,4,2},
        {4,9,6,1,8,2,5,7,3},
        {2,8,5,4,7,3,9,1,6}  };
        
        
/*
Es el arreglo donde los hilos guardaran el resultado de su analisis
*/
char validadores[MAX*3] = {0};


int main(){
    /*
    Este es un arreglo tipo pthread_t para almacenar los id de los hiilos que main crea,
    tiene 27 espaciones
    */
    pthread_t hilos[MAX*3];
    
   /*
    Una matriz 9x2, donde se encuentran las posiciones de las minimatrices 3x3, es usada en la
    asignacion de posiciones para los hilos que trabajaran en la funcion worker_thread_square.
    */
    char posiciones[MAX][2] = {{0,0},{3,0},{6,0},{0,3},{3,3},{6,3},{0,6},{3,6},{6,6}};

   /*
    Puntero tipo parameters para almacenar el puntero que me retorna malloc, se usa malloc 
    para separar un espacio para almacenar el contenido del struct parameters, porque recuerde
    que los hilos comparten el HEAP, si se enviara un struct a la funcion cuyo contenido esta
    en el STACK, entonces daria error.
    Este puntero se envia a la funcion callback del hilo correspondiente
    */
    parameters *parametro = NULL;
    
    /*
    Bandera usada para controlar si la respuesta del sudoku es valida o no
    */
    char flag = 1;

   /*
    Imprime el sudoku
    */
    print_sudoku();

   /*
    Se necesita solo un for que realice 9 iteraciones, porque se va a crear 27 hilos, donde 9 
    revisaran filas, otras 9 colummnas y los ultimos 9 las minimatrices 3x3
    De tal forma, se que del arreglo pthread_T hilos, en las posiciones
    [0-8] --> Hilos analizan filas
    [9-17] --> Hilos analizan colummnas
    [18-26] --> Hilos analizan minimatriz 3x3
    */
    for(int i=0;i<MAX;i++){
    	 /*
    	En esta seccion se inicializan los hilos que realizaran analisis de las filas, por 		eso para cada hilo se le asignara su fila(row) correspondiente
    	*/
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = i;
        parametro->column = 0;
        parametro->posicion = i;
	pthread_create(&hilos[i],NULL,worker_thread_row,(void *) parametro);
	
	/*
    	En esta seccion se inicializan los hilos que realizaran analisis de las columnas, por 		eso para cada hilo se le asignara su columna(column) correspondiente, recordar que 
    	estos hilos estaran en la posicion 9-17, por eso la suma del +9 en el pthread_create
    	*/
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = 0;
        parametro->column = i;
        parametro->posicion = i + 9;
        pthread_create(&hilos[i+9],NULL,worker_thread_column,(void *) parametro);
        
        /*
    	En esta seccion se inicializan los hilos que realizaran analisis de las minimatrices 
    	3x3, por eso para cada hilo se le asignara la fila y columna donde la minimatriz 3x3
    	correspondiente comience.
    	Recordar que estos hilos estaran en la posicion 18-26, por eso la suma del +18 en el
    	pthread_create
    	*/
        parametro = (parameters *) malloc(sizeof(parameters));
        parametro->row = posiciones[i][0];
        parametro->column = posiciones[i][1];
        parametro->posicion = i + 18;
        pthread_create(&hilos[i+18],NULL,worker_thread_square,(void *) parametro);
    }

    /*
    Con este for, el main thread recoge a los 27 hilos que origino
    */
    for(int i = 0; i<MAX*3; i++){
    	//Espera que el hilo en esa posicion termine
        pthread_join(hilos[i],NULL);
        /*
        Se usa el operado & que es una operacion que hace el AND a nivel de bit
        Ej: flag inicia en 1, como flag es un char, pesa 1 byte -- 8bit
        1 en 8 bits es 00000001
        Si el hilo i en su analisis, guarda un 1, entonces validadores[i] = 1
        en 8 bits es 00000001
        Por lo que el operador & hara la conjuncion bit por bit con ambas variables
        flag 		-->		00000001
        validadores[i] -->	     &	00000001
        				--------
        Resultado	-->		00000001
        
        Si validadores[i] fuese cero
        flag 		-->		00000001
        validadores[i] -->	     &	00000000
        				--------
        Resultado	-->		00000000
        
        Es el mismo resultado si flag fuese cero
        Recuerde que en conjuntos el operador and da el valor de 1 cuando ambos bit son 1
        caso contrario es cero
        */
        flag &= validadores[i];    
    }

    /*
    Chequea el resultado final de flag, una vez revisado todos los resultados del analisis de
    los hilos
    */
    if(flag)
        printf("Solucion de Sudoku es valida\n");
    else
        printf("Solucion de Sudoku es invalida\n");
    
    return 0;
}

/*
Esta es la funcion callback de un hilo que tiene que verificar una sola fila
Se usa un for para recorrer la fila, donde la posicion de la fila se mantiene constante y se mueve por las columnas
*/
void *worker_thread_row(void *parameter){
    /*
    Se hace un casting al parametro enviado para poderlo usar
    */
    parameters *parametro = (parameters *) parameter;
    
    /*
    Es un arreglo de 9 posiciones usado para controlar si todos los numeros son del 1-9
    */
    char checker[MAX] = {0};
    
    /*
    Bandera usada para registrar el resultado de analisis de los hilos
    */
    char flag = 1;
    
    /*
    Es usado para almacenar el valor de la posicion actual en la matriz, usado para acceder
    a la posicion del arreglo checker
    */
    char pos = -1;
    
    
    /*
    Se itera la fila correspondiente
    */
    for(int i=0;i<MAX;i++){
    	/*
    	obtenemos el valor de la posicion actual de la matriz, y se le resta uno para poder 
    	entrar a la posicion correspondiente de checker porque los indices de este arreglo
    	es de 0-8
    	*/
        pos = (sudoku[parametro->row][i]) - 1;
        
        /*
        Evalua el valor de la casilla de checker, si checker[pos] es 0, entonces ese numero,
        todavia no ha sido registrado en el analisis y se cambia el valor a 1 porque ya esta
        siendo registrado en ese momento, en cambio si es 1, entonces ese numero ya fue
        registrado anteriormente, por lo que se repite, entonces ya aqui, la solucion
        del sudoku ya no es valida, y el resultado del analisis debe ser 0, por eso en el 
        else, flag se asigna a cero
        */
        if(!checker[pos])
            checker[pos] = 1;
        else
            flag = 0;
    }

    /*
    Si flag es uno, entonces analisis ha verificado que la fila es correcta, entonces guarda
    su resultado en la casilla del arreglo de validadores correspondiente.
    Si flag es cero, no se hace nada, porque arrelgo de validadores inicializo todas sus
    casilas en 0, y eso corresponde a que el analisis de ese hilo arrojo un resultado negativo
    */
    if(flag)
        validadores[parametro->posicion] = 1;
    
    //Se libera la estructura reservada por malloc, para liberar recursos
    free(parametro);
    
    /*
    Todo este analisis de esta funcion se repite para las dos segundas funciones
    */
    return NULL;   
}


/*
Esta es la funcion callback de un hilo que tiene que verificar una sola columna
Se usa un for para recorrer la columna, donde la posicion de la columna se mantiene constante y se mueve por las filas
*/
void *worker_thread_column(void *parameter){
    parameters *parametro = (parameters *) parameter;
    char checker[MAX] = {0};
    char flag = 1;
    char pos = -1;
    
    for(int i=0;i<MAX;i++){
        pos = (sudoku[i][parametro->column]) -1;
        if(!checker[pos])
            checker[pos] = 1;
        else 
            flag = 0;
        
    }

    if(flag)
        validadores[parametro->posicion] = 1;
    
    free(parametro);
    return NULL;
}


/*
Esta es la funcion callback de un hilo que tiene que verificar una minimatriz 3x3
Se usa un for para recorrer la matriz, tomando en consideracion que el contenido de la matriz
se compone de la siguiente manera, y conociendo que la fila y columna han sido enviados como parametro
			colummna	columna + 1	colummna +2
	fila	
	fila +1
	fila +2
*/
void *worker_thread_square(void *parameter){
    parameters *parametro = (parameters *) parameter;
    char checker[MAX] = {0};
    char flag = 1;
    char pos = -1;

    for(int i=parametro->row;i<(parametro->row) + 3;i++){
        for(int j=parametro->column;j<(parametro->column) + 3;j++){
            pos = (sudoku[i][j]) - 1; 
            if(!checker[pos])
                checker[pos] = 1;
            else 
                flag = 0;
        }
    }

    if(flag)
        validadores[parametro->posicion] = 1;
    

    free(parametro);
    return NULL;
}

/*
Sirve para dar un diseño a la impresion de una solucion de sudoku
*/
void print_sudoku(){

    printf("Imprimiendo Sudoku:\n");

    for(int i=0;i<MAX;i++){
        printf("-------------------\n");
        printf("|");

        for(int j=0;j<MAX;j++)
            printf("%d|",sudoku[i][j]);
        
        printf("\n");
    }
    printf("-------------------\n");
}

/*
Limitaciones:
* Cada hilo usa un arreglo de tamaño 9 para validar si el numero ya esta repetido.
* La solucion del sudoku esta quemada en el codigo

Complicaciones:
* Pensar como pasar las posiciones de la minimatriz, se resolvio realizar una matriz que contenga las posiciones iniciales de la minimatriz
* Al principio se tenian tres for para iniciar cada grupo de hilos, pero despues se decidio usar 9 hilos para revisar filas, 9 para colummnas y 9 para minimatrices, y como es el mismo numero de hilos para cada cosa, se pudo unirlos en un solo for que en cada iteracion inicializa un hilo para fila, uno para columna, y otro para minimatriz.
* No se sabia como verificar que digitos no esten repetidos, pero se resolvio que cada hilo tenga un arreglo char de 9 posiciones que lo usan para validar si digito ya ha sido validado, verificando si valor es uno o cero

*/


