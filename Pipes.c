/******************************************************************************pi
Servidor FIFO sin Nombre
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    char buffer[100];
//mknod() - mkfifo()
int fd[2];//0 - lectura 1 - escritura
pipe(fd);
switch(fork())
{
    case 0: //hijo - recibir

    close(fd[1]);
    read(fd[0],buffer,sizeof(buffer));
    printf("%s\n",buffer);
    break;
    default: //padre
    close(fd[0]);

    strcpy(buffer,"saludos");
    write(fd[1],buffer,sizeof(buffer));
    close(fd[1]);
    break;
}
return 0;
}