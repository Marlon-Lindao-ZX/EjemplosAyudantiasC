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
#include "csapp.h"

#define MAXSIZE 1024

//int read_response(int fd, char *filename);
void handler_client(int connfd);
