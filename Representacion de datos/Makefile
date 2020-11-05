
all: create representacion

create:
	mkdir -p bin obj

representacion: obj/main.o obj/conversion.o
	gcc obj/main.o obj/conversion.o -o bin/representacion

obj/main.o: src/main.c include/general.h
	gcc -c src/main.c -o obj/main.o

obj/conversion.o: src/conversion.c include/general.h
	gcc -c src/conversion.c -o obj/conversion.o

.PHONY: clean

clean:
	rm bin/* obj/*



