#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct Datos{
    char nombre[20];
    int opc;
    char respuesta[100];
};

int main()
{
    int i, pid, status, fdr, fdw;
    struct Datos info;
    system("mkfifo servidor"); //Abrir conexion
    fdr = open("servidor",O_RDONLY);
    pid = fork();
    switch (pid)
    {
    case -1:
        /* An error has occurred */
        printf("Fork Error");
        break;

        break;
    case 0:
        /* This code is executed by the first parent */
        printf("Hola");
        break;
    default:
        /* This code is executed by the parent process */
        read(fdr,&info, sizeof(info));
        printf("usuario:%s,opcion%i\n",info.nombre,info.opc);
        fdw = open(info.nombre,O_WRONLY);
        strcpy(info.respuesta,info.nombre);
        strcat(info.respuesta, ": Esta es tu respuesta\n");
        write(fdw,&info, sizeof(info));
        close(fdw);

    }
}
