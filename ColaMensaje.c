/******************************************************************************
 mq = msgget( key, IPC_CREAT | 0666 );    110 110 110
msgsnd( mq, &mensaje, sizeof (mensaje), 0 );   // mensaje es una variable de tipo  struct buffer
msgrcv( mq, &mensaje, sizeof (mensaje), 1, 0 );  // en ambos casos regresa -1 en caso de error

*******************************************************************************/
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
    
    printf("QUien eres");
    scanf("%d",&yo);

    printf("id destino:");
    
    scanf("%ld",&mensaje.id);
    getchar();
    printf("mensaje:");
    gets(mensaje.msj);
    msgsnd( mq, &mensaje, sizeof (mensaje), 0 );   // mensaje es una variable de tipo  struct buffer
    printf("mensaje enviado");

    getchar();
    strcpy(mensaje.msj,"");
    msgrcv( mq, &mensaje, sizeof (mensaje),yo , 0 );
    printf("el mensaje par mi es: %s\n",mensaje.msj);

    return 0;
}