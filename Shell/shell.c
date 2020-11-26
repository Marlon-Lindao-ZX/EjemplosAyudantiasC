#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <errno.h>
#include <semaphore.h>

#define MAX 100
#define MAX2 1024

#define STDIN 0
#define STDOUT 1

void build(char data[], char *argv[])
{
    const char s[4] = " \t\n";
    char *token;
    int i = 0;
    token = strtok(data, s);
    while (token != NULL)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, s);
    }
    argv[i] = NULL;
}

int main(int argc, char **argv)
{

    char buffer2[MAX2] = {0};

    char *buffer;
    size_t tam = MAX2;

    char *argumento[MAX] = {0};

    size_t line = 0;

    pid_t pid = {0};

    int status;

    int stdin_copy;

    printf(">>");

    while ((line = getline(&buffer, &tam, stdin)) != -1)
    {

        if (strcmp(buffer, "exit\n") == 0)
        {
            break;
        }

        int p[2];

        if (pipe(p) < 0)
        {
            fprintf(stderr, "Error al llamar a la funcion pipe()\n");
            exit(1);
        }

        build(buffer, argumento);

        int stdin_copy = dup(STDIN);

        if ((pid = fork()) == 0)
        {
            close(STDOUT);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            execvp(argumento[0], argumento);
            fprintf(stderr, "Error al llamar a la funcion execvp()\n");
            exit(-1);
        }
        else
        {
            if (waitpid(pid, &status, 0) > 0)
            {
                close(STDIN);
                int fd = dup(p[0]);
                close(p[0]);
                close(p[1]);
                ssize_t readed, writed;

                while ((readed = read(fd, buffer2, MAX2) != 0))
                {
                    if (readed < 0)
                    {
                        fprintf(stderr, "Error al leer\n");
                        exit(-1);
                    }

                    writed = write(STDOUT, buffer2, MAX2);

                    if (writed < 0)
                    {
                        fprintf(stderr, "Error al escribir al stdout\n");
                        exit(-1);
                    }

                    memset(buffer2, 0, MAX2);
                }
                
                dup2(stdin_copy, STDIN);
                printf(">>");
            }
            else
            {
                fprintf(stderr, "Error al llamar a la funcion waitpid()\n");
                exit(-1);
            }
        }
    }

    return 0;
}