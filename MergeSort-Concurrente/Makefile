
mergesort: obj/archivo.o obj/hilo.o obj/input.o obj/main.o obj/opciones.o obj/cola.o obj/mergesort.o
	gcc obj/main.o obj/archivo.o obj/hilo.o obj/input.o obj/opciones.o obj/cola.o obj/mergesort.o -lpthread -o bin/mergesort

obj/archivo.o: src/archivo.c include/general.h
	gcc -c src/archivo.c -o obj/archivo.o

obj/hilo.o: src/hilo.c include/general.h
	gcc -c src/hilo.c -o obj/hilo.o

obj/input.o: src/input.c include/general.h
	gcc -c src/input.c -o obj/input.o

obj/opciones.o: src/opciones.c include/general.h
	gcc -c src/opciones.c -o obj/opciones.o

obj/cola.o: src/cola.c include/general.h
	gcc -c src/cola.c -o obj/cola.o

obj/mergesort.o: src/mergesort.c include/general.h
	gcc -c src/mergesort.c -o obj/mergesort.o

obj/main.o: src/main.c include/general.h
	gcc -c src/main.c -o obj/main.o

.PHONY: clean

clean:
	rm bin/* obj/*
