#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct info
{
    long id;
    char msj[100];
};
int main()
{
    int mq;
    int yo;
    struct info mensaje; //yo soy el usuario 1
    mq = msgget( 123, IPC_CREAT | 600 | IPC_NOWAIT ); 

    perror("");
    
    printf("Quien eres: ");
    scanf("%d",&yo);

    printf("ID destino: ");
    scanf("%ld",&mensaje.id);
    getchar();

    printf("Mensaje: ");
    gets(mensaje.msj);

    msgsnd(mq, &mensaje, sizeof (mensaje), 0 );   // mensaje es una variable de tipo  struct buffer
    printf("Mensaje enviado");
    getchar();

    strcpy(mensaje.msj,"");
    msgrcv(mq, &mensaje, sizeof (mensaje), yo, 0 );
    printf("El mensaje para mi es: %s\n",mensaje.msj);

    return 0;
}