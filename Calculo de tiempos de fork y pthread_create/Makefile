all: fork thread

fork: timefork.o
	gcc timefork.o -o fork

thread: timethread.o
	gcc timethread.o -o thread -lpthread

timefork.o: timefork.c
	gcc -c timefork.c

timethread.o: timethread.c
	gcc -c timethread.c

.PHONY: clean

clean:
	rm *.o fork thread
