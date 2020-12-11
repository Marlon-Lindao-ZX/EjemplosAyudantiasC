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
			case 'f':
				filename = optarg;
				break;
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

	host = argv[optind];
	port = argv[optind + 1];

	clientfd = Open_clientfd(host, port);

	char buffer[MAXSIZE] = {0};
    char requerimiento[MAXSIZE] = {0};

	strcat(requerimiento, "GET ");
	strcat(requerimiento, filename);

	if(send(clientfd,requerimiento,MAXSIZE,0) < 0){
        fprintf(stderr,"Requerimiento no pudo ser enviada\n");
    }

	if(recv(clientfd,buffer,MAXSIZE,0) < 0){
        fprintf(stderr,"No se recibio respuesta de servidor\n");
    }else{
		printf("%s\n",buffer);
	}
	
	exit(0);
}