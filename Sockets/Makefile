
all: client server

client: client.o csapp.o
	gcc client.o csapp.o -o client -lpthread

server: server.o csapp.o
	gcc server.o csapp.o -o server -lpthread

client.o: client.c general.h
	gcc -c client.c

server.o: server.c general.h
	gcc -c server.c

csapp.o: csapp.c csapp.h
	gcc -c csapp.c

.PHONY: clean

clean:
	rm *.o client server