
mergesort: obj/archivo.o obj/hilo.o obj/input.o obj/main.o obj/opciones.o obj/cola.o
	gcc obj/main.o obj/archivo.o obj/hilo.o obj/input.o obj/opciones.o obj/cola.o -o bin/mergesort

obj/%.o: src/%.c include/general.h
	gcc -c src/%.c -o obj/%.o

.PHONY: clean

clean:
	rm bin/* obj/*
