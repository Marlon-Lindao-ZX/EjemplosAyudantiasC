
bin/cola: obj/cola.o obj/main.o
	gcc -Wall obj/main.o obj/cola.o -o bin/cola -fsanitize=address,undefined

obj/cola.o: src/cola.c include/cola.h
	gcc -Wall -c src/cola.c -o obj/cola.o

obj/main.o: src/main.c include/cola.h
	gcc -Wall -c src/main.c -o obj/main.o

.PHONY: clean

clean:
	rm bin/* obj/*
