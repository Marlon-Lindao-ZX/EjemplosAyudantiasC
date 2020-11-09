Lib=general.h

all: timeshmm timepipe

timeshmm: timeshmm.o $(LIB)
	gcc timeshmm.o -o timeshmm -lrt

timepipe: timepipe.o $(LIB)
	gcc timepipe.o -o timepipe

timeshmm.o: timeshmm.c $(LIB)
	gcc -c timeshmm.c

timepipe.o: timepipe.c $(LIB)
	gcc -c timepipe.c

.PHONY: clean

clean:
	rm *.o timeshmm timepipe

