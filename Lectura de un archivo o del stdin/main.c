#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>  
#include <errno.h>  
#include <string.h>  

#define MAX 100

int open_file(char *filename);
void check_error(char *message);
void read_and_write(int fd);

int main(int argc, char** argv) {
    char * name;
    char output;

    int fd;

    switch(argc){
        case 1:
            if(isatty(STDIN_FILENO)){
                fprintf(stderr,"No hay dato en stdin\n");
                fprintf(stderr, "Error de uso: \"./mycat filename\" or \"bash command |  ./mycat\"\n");
                exit(EXIT_FAILURE);
            }
            fd = STDIN_FILENO;
            break;
        case 2:
            fd = open_file(argv[1]);
            break;
        default:
            fprintf(stderr, "Error de uso: \"./mycat filename\" or \"bash command |  ./mycat\"\n");
            exit(EXIT_FAILURE);

    }

    read_and_write(fd);
    
    if(fd == 2){
        close(fd);
    }
    exit(EXIT_SUCCESS);
}

void read_and_write(int fd){
    char buffer[MAX];
    ssize_t readed, writed;
    
    while((readed = read(fd,buffer,MAX) != 0)){

        if(readed < 0)
            check_error("Error al leer\n");
        
        writed = write(STDOUT_FILENO,buffer,MAX);

        if(writed < 0)
            check_error("Error al escribir al stdout\n");

        memset(buffer,0,MAX);

    }


}

void check_error(char *message){
    fprintf(stderr, "%s\n",message);
    fprintf(stderr,"Codigo de error: %d\n",errno);
    fprintf(stderr, "Descripcion del error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

int open_file(char *filename){
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        check_error("Error al abrir archivo\n");
    }
}