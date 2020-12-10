#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXSIZE 2048

int open_clientfd(char *hostname, char *port);
int read_response(int fd, char *filename);