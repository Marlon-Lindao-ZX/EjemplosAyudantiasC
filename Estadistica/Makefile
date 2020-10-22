Lib=general.h

estadistica: main.o input.o $(Lib)
	gcc main.o input.o -o estadistica

main.o: main.c
	gcc -c main.c

input.o: input.c
	gcc -c input.c

.PHONY: clean

clean:
	rm *.o estadistica
