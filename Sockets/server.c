#include "general.h"

int main(int argc, char **argv){
    int listenfd, connfd;
	unsigned int clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp, *port;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	port = argv[1];
	listenfd = Open_listenfd(port);
	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

		/* Determine the domain name and IP address of the client */
		hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
					sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("server connected to %s (%s)\n", hp->h_name, haddrp);

        //Atencion al cliente
        handler_client(connfd);
		
		Close(connfd);	
	}
	exit(0);
}

void handler_client(int connfd){
    char buffer[MAXSIZE] = {0};
    char respuesta[MAXSIZE] = {0};
    char validador = 1;

    if(recv(connfd,buffer,MAXSIZE,0) < 0){
        fprintf(stderr,"No se recibio mensaje de cliente\n");
        validador = 0;
    }

    if(validador){
        strcat(respuesta,"Recibido: ");
        strcat(respuesta,buffer);
    }else{
        strcat(respuesta,"Requerimiento perdido\n");
    }

    if(send(connfd,respuesta,strlen(respuesta),0) < 0){
        fprintf(stderr,"Respuesta no pudo ser enviada\n");
    }

}
