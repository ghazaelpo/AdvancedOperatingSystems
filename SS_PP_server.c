/*pipe con nombre fifo 10k*/
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
    if(fdr ==-1)
    {
            perror("");
        exit(1);

    }
    printf("Servidor iniciado\n Bienvenido!\n A que menu deseas ingresar:\n");
    printf("1)Servicio social\n 2)Practicas profesionales");
    do{
        read(fdr,&info, sizeof(info));
        printf("usuario:%s,opcion%i\n",info.nombre,info.opc);
        fdw = open(info.nombre,O_WRONLY);
        strcpy(info.respuesta,info.nombre);
        strcat(info.respuesta, ": Esta es tu respuesta\n");
        write(fdw,&info, sizeof(info));
        close(fdw);
    }
    while(1);
    
    return 0;
}