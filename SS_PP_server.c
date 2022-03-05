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
int main(){
    int fdr, fdw;
    struct Datos info;
    system("mkfifo servidor"); //Abrir conexion
    fdr = open("servidor",O_RDONLY);

    switch(fork())
    {
        case 0:
        perror("");
        break;

        case 1:
        read(fdr,&info, sizeof(info));
        printf("usuario:%s,opcion%i\n",info.nombre,info.opc);
        fdw = open(info.nombre,O_WRONLY);
        strcpy(info.respuesta,info.nombre);
        strcat(info.respuesta, ": Esta es tu respuesta\n");
        write(fdw,&info, sizeof(info));
        close(fdw);
        break;
    }
    return 0;
}
