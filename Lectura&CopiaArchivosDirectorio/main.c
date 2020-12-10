#include "general.h"

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        fprintf(stderr, "Cantidad de argumentos no validos\n");
        fprintf(stderr, "Uso: %s <directorio_fuente> <directorio_destino>\n", argv[0]);
        return -1;
    }

    DIR *folderO = NULL;
    DIR *folderD = NULL;
    DIR *temporal = NULL;

    char pathO[MAX] = {0};
    char pathD[MAX] = {0};

    char buffer[SIZE] = {0};

    size_t readed, writed, tam = 0;

    int temp = 0;

    int fd1, fd2 = 0;

    char *folderOrigen = argv[1];
    char *folderDestino = argv[2];

    struct dirent *archivoO = NULL;
    struct dirent *archivoD = NULL;

    folderO = opendir(folderOrigen);

    if (folderO == NULL)
    {
        fprintf(stderr, "Directorio %s no pudo ser abierto (no existe o no tenemos permiso para acceder\n", folderOrigen);
        return -1;
    }

    folderD = opendir(folderDestino);

    if (folderD == NULL)
    {
        if (mkdir(folderDestino, 0777) < 0)
        {
            fprintf(stderr, "Directorio %s no pudo ser creado\n", folderDestino);
            return -1;
        }

        folderD = opendir(folderDestino);

        if (folderD == NULL)
        {
            fprintf(stderr, "Directorio %s no pudo ser abierto\n", folderDestino);
            return -1;
        }
    }

    while ((archivoO = readdir(folderO)) != NULL)
    {
        if (strcmp(archivoO->d_name, ".") != 0 && strcmp(archivoO->d_name, "..") != 0)
        {
            temporal = opendir(archivoO->d_name);
            if (temporal == NULL)
            {
                strcat(pathO, folderOrigen);
                temp = strlen(folderOrigen);
                if (folderOrigen[temp - 1] != '/')
                    strcat(pathO, "/");
                strcat(pathO, archivoO->d_name);

                strcat(pathD, folderDestino);
                temp = strlen(folderDestino);
                if (folderDestino[temp - 1] != '/')
                    strcat(pathD, "/");
                strcat(pathD, archivoO->d_name);

                int fd1 = open(pathO, O_RDONLY);

                if (fd1 < 0)
                {
                    fprintf(stderr,"Archivo %s no pudo ser abierto\n", pathO);
                    return -1;
                }

                int fd2 = open(pathD, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0666);

                if (fd2 < 0)
                    fprintf(stderr,"Archivo %s no pudo ser abierto\n", pathD);

                if (fd1 > 0 && fd2 > 0)
                {

                    while ((readed = read(fd1, buffer, SIZE)) > 0)
                    {

                        if (writed = write(fd2, buffer, readed) < 0)
                        {
                            fprintf(stderr, "Error al escribir en %s\n", pathD);
                            break;
                        }

                        if (lseek(fd2, 0, SEEK_END) < 0)
                        {
                            fprintf(stderr, "Error al desplazar el puntero interno de %s\n", pathD);
                            break;
                        }

                        tam += readed;
                        memset(buffer,0,SIZE);
                    }

                    printf("Se copiaron %ld bytes de %s a %s\n", tam, pathO, pathD);
                    tam = 0;
                }
                if(fd1 >0)
                    close(fd1);
                if(fd2 >0)
                    close(fd2);

                memset(buffer,0,SIZE);
                memset(pathO, 0, MAX);
                memset(pathD, 0, MAX);
            }
            else
            {
                closedir(temporal);
            }
        }
    }

    closedir(folderO);
    closedir(folderD);

    return 0;
}