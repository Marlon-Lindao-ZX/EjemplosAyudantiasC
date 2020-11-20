
all: head tail

head: head.o compartido.o
	gcc head.o compartido.o -o head

head.o: head.c general.h
	gcc -c head.c

tail: tail.o compartido.o
	gcc tail.o compartido.o -o tail

tail.o: tail.c general.h
	gcc -c tail.c

compartido.o: compartido.c general.h
	gcc -c compartido.c

.PHONY: clean

clean:
	rm -f *.o head tail
