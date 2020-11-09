
sudoku: main.o 
	gcc main.o -lpthread -o sudoku

main.o: main.c
	gcc -c main.c

.PHONY: clean

clean:
	rm *.o sudoku
