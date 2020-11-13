
test: main.o ex.o
	gcc -o test main.o ex.o

main.o: main.c general.h
	gcc -c main.c

ex.o: ex.c general.h
	gcc -c ex.c

.PHONY: clean

clean:
	rm *.o test
