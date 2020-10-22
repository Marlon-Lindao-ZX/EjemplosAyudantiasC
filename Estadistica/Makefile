Lib=general.h

estadistica: main.o input.o estadistica.o $(Lib)
	gcc main.o input.o estadistica.o -o estadistica

main.o: main.c
	gcc -c main.c

input.o: input.c
	gcc -c input.c

estadistica.o: estadistica.c
	gcc -c estadistica.c

.PHONY: clean

clean:
	rm *.o estadistica
