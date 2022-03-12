#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct Datos
{
    char nombre[20];
    int opc;
    char respuesta[100];
};
struct info
{
    long id;
    char msg[100];
};

int main()
{
    int fd[2];
    int fdr, fdw;
    char buffer[100];
    struct Datos info;
    system("mkfifo servidor"); // Abrir conexion
    fdr = open("servidor", O_RDONLY);
    if (fdr == -1 | pipe(fd) == -1)
    {
        perror("");
        exit(1);
    }

    printf("------Servidor inicializado------\n");
    printf("**********Bienvenido**********\nPor favor selecciona una opción:\n");
    printf("1) Servicio Social\n2) Prácticas profesionales\n");

    read(fdr, &info, sizeof(info));
    printf("Usuario: %s, opción %i\n", info.nombre, info.opc);
    fdw = open(info.nombre, O_WRONLY);
    write(fdw, &info, sizeof(info));

    if (info.opc == 2)
    {

        int mq;
        int pid;
        int id_server = 100;
        struct info mensaje;
        mq = msgget(123, IPC_CREAT | 600 | IPC_NOWAIT);

        perror("");


        if (mq == -1)
        {
            perror("");
        }

        pid = fork(); // -1, 0 everything before this the son process inherited ,
                      // PID is return to the father process
        switch (pid)
        {
        case -1:
            perror("");
            break;
        case 0: // son code
            printf("Proceso hijo Practicas Profesionales %i\n", getpid());
            printf("Intel\nBosch\nContinental\nCapgemini\nModutram\n");

            int fd_db;

            fd_db = open("pp.txt", O_RDONLY);

            if (fd_db == -1)
            {

                perror("");
            }
            else
            {
                read(fd_db, buffer, sizeof(buffer));
                close(fd_db);
                mensaje.id = id_server;
                strcpy(mensaje.msg, buffer);
                msgsnd(mq, &mensaje, sizeof(mensaje), 0);
            }
            break;
        default:
            msgrcv(mq, &mensaje, sizeof(mensaje), id_server, 0);
            printf("El mensaje es: %s\n", mensaje.msg);
            strcpy(info.respuesta, mensaje.msg);
            msgctl(mq, IPC_RMID, NULL);
            break;
        }
    }

    if (info.opc == 1)
    {
        
        

        int id = fork();
        if (id == 0)
        {
            
            close(fd[0]);
            write(fd[1], &info.opc, sizeof(int));
            close(fd[1]);
            close(fdw);
        }

        else
        {
            close(fd[1]);
            read(fd[0], &info.opc, sizeof(int));
            close(fd[0]);
            printf("Proceso hijo Servicio Social: %i\n", id);
            printf("Siteur\nGobierno de Jalisco\nSAT\n");
        }
    }

    return 0;
}
