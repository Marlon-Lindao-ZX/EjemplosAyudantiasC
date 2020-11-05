# EjemplosAyudantiasC
Este repositorio va a ser usado para almacenar los programas ejemplos que sean creados en las ayudantías:
- Estadistica --> Contiene un programa para calcular la media y varianza de una lista de numeros ingresados por el usuario
- Punteros --> Contiene las bases de los punteros, como usarlos y la aritmética de los mismos
- Programa con Opciones --> Contiene las bases para realizar un programa que reciba opciones como el comando ls que tiene opciones como el -l o -a
- Programa de lectura de archivos o de entrada del usuario --> Contiene un programa aplicando opciones, simulando el comando head, y se muestra como se puede leer un archivo o la entrada estandar del sistema(stdin). Para probarlo, usar la opcion -f para indicar el nombre del archivo, y usar la opcion -n para indicar el numero de lineas a leer.
Si ven el video, veran que se uso la funcion fopen, aqui dejo el link de los modos que se puede usar para abrir el archivo -> [Ver modos del fopen](https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm)
- Lectura de archivo o entrada del stdin --> Este es un programa que toca temas que veran en el segundo parcial, este programa imprime el contenido de un archivo por la consola, inclusive puede imprimir lo que se envia por la entrada estandar del sistema(ej: cat names.data | ./mycat)

## Caracteres Especiales usados en la familia de funciones de printf y scanf
- %c --> para para imprimir o capturar un caracter en codigo ASCII (char, ej: si declare una variable char c = 88, al usar este caracter, en la consola me imprime el valor de X)
- %d --> para imprimir o capturar variables numericos enteros(char, short, int)
- %ld --> para imprimir o capturar variables numericos enteros grandes (long, long long) --> l es el caracter para aumentar el tamaño
- %f --> para imprimir o capturar variables numericos decimales (float)
- %.numerof --> un tipo de caracter especial para imprimir o capturar un numero determinado de decimales(ej: %.2f --> imprimo dos primeros decimales del float)
- %s --> para imprimir o capturar cadenas de caracteres(String --> char array[Cantidad de Caracteres])
- %p --> para imprimir direcciones de memoria
- %x --> para imprimir el valor de una variable en formato hexadecimal
- %o --> para imprimir el valor de una variable en formato octal

##Representacion de datos

		Tabla de Tamaño de los tipos de datos

		tipo dato			Arquitectura-32bit	Arquitectura-64bit
		char					1byte			1byte
		short					2byte			2byte
		int					4byte			4byte
		long					4byte			8byte
		long long				8byte			8byte
		float					4byte			4byte
		double					8byte			8byte
		punteros(direccion de memoria)		4byte			8byte	

		Para representar datos, se usa la notacion hexadecimal:
		Porque con dos digitos hexadecimales, puedo representar un byte
		Entonces cuando me piden representar datos en memoria, me dicen que transforme el dato en hexadecimal

		Little Endian y Big Endian --> byte mas significativo, es el byte que tiene mas peso de la cadena bytes

		Little Endian --> Byte mas significativo va al ultimo
		Big Endian --> Byte mas significativo va al principio

		Los pasos para representar datos en memoria:
		1) Ver la arquitectura que me estan dando en el problema
		2) Ver el tamaño del dato respecto a la arquitectura
		3) Convertir el dato a hexadecimal
		4) Llenar con ceros a la izquierda para tener los bytes completos
		5) Ver si es little endian o big endian, esto es ver si me lo especifican en el enunciado
		6) Con 4), representar el dato


		Ejemplo:
		Represente la variable 
		int x = 42 
		en memoria

		Voy a asumir que trabajo con arquitectura de 32 bit
		variable x tiene un tamaño de 4 bytes
		
		Convertir el 42 a hexadecimal
		
		42 	|_16
		32	2	|_16
		(10)	0	0	
			(2)

		recordar que los digitos hexadecimales van del 0 hasta el 15 --> (0 - F)
		0		8 
		1		9
		2		A --> 10
		3		B --> 11
		4		C --> 12
		5		D --> 13
		6		E --> 14
		7		F --> 15


		El 42 en hexadecimal es 2A
		
		00 00 00 2A 	----> 	00 --> Este es byte mas significativo
					00
					00
					2A --> Este es el byte menos significativo

		LA representacion en litte endian es:
		2A 00 00 00

		La representacion en big endian es:
		00 00 00 2A

## Direccion web donde pueden ver como modificar un README:
[Sintaxis Readme](https://docs.github.com/es/free-pro-team@latest/github/writing-on-github/basic-writing-and-formatting-syntax)

## Autor
Marlon Eddie Lindao Varas
