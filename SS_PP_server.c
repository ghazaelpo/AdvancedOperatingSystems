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
struct Datos info;
int server(){
    int fdr, fdw;
    
    system("mkfifo servidor"); //Abrir conexion
    fdr = open("servidor",O_RDONLY);
    if(fdr ==-1)
    {
            perror("");
        exit(1);

    }
    printf("Servidor iniciado\n Bienvenido!\n A que menu deseas ingresar:\n");
    printf(" 1)Servicio social\n 2)Practicas profesionales\n");
    printf("\n");
    read(fdr,&info, sizeof(info));
    printf("Usuario: %s, opcion %i\n",info.nombre,info.opc);
    fdw = open(info.nombre,O_WRONLY);
    write(fdw,&info, sizeof(info));
    close(fdw);
    
    return 0;
}

int main(){
    server();
    char buffer[100];
    int fd[2];//0 - lectura 1 - escritura
    pipe(fd);
    switch(fork())
    {
        case 0: //hijo - recibir
        close(fd[1]);
        read(fd[0],buffer,sizeof(buffer));
        printf("%s\n",buffer);
        if (info.opc == 1){
            printf("1.- Siteur\n2.- Cervecería Moctezuma\n3.- Gobierno del Estado ");
        }
        if (info.opc == 2){
            printf("1.- Continental\n2.- Bosch\n3.- Osram");
        }
        break;
        
        default: //padre
        close(fd[0]);
        strcpy(buffer,"\nEmpresas disponibles:");
        write(fd[1],buffer,sizeof(buffer));
        close(fd[1]);
        break;
    }
    return 0;
}
