#include "general.h"

int main(int argc, char **argv)
{
	int clientfd;
	int non_option_arguments = 0, index, n;
	char c;
	char *filename = NULL;
	char *host, *port = NULL;
	char buf[5*MAXSIZE];

	while ((c = getopt (argc, argv, "f:h")) != -1) {
		switch(c){
			case 'h':
				printf("%s prueba la conexion a un socket.\n\n", argv[0]);
				printf("Options:\n  -h\t\t\tHelp, show this message.\n");
				return 0;
			default:
				fprintf(stderr, "usage: %s [-f <filename>] <host> <port>\n", argv[0]);
				exit(0);
		}
	}

	for (index = optind; index < argc; index++)
		non_option_arguments++;

	if (non_option_arguments != 2) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
    printf("%s\n", host);
	port = argv[2];
    printf("%s\n", port);

	clientfd = open_clientfd(host, port);

	if(clientfd > 0){
		printf("Conexion exitosa\n");
	}else
		fprintf(stderr, "No es posible conectarse a %s:%s\nError: %s\n", host,port,strerror(errno));

	
	exit(0);
}

int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints; 
    struct addrinfo *listp, *p;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  /* Open a connection */
    hints.ai_flags = AI_NUMERICSERV;  /* ... using a numeric port arg. */
    hints.ai_flags |= AI_ADDRCONFIG;  /* Recommended for connections */
    getaddrinfo(hostname, port, &hints, &listp);
  
    /* Walk the list for one that we can successfully connect to */
    for (p = listp; p; p = p->ai_next) {

        /* Create the socket descriptor */
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue; /* Socket failed, try the next */
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
            break; /* Success */
        close(clientfd); /* Connect failed, try another */
    } 

    /* Clean up */
    freeaddrinfo(listp);
    if (!p) /* All connects failed */
        return -1;
    else    /* The last connect succeeded */
        return clientfd;
}