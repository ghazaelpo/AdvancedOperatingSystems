#include <stdio.h>

int main()
{
//mknod() - mkfifo()
int fd[2];//0 - lectura 1 - escritura
pipe(fd);
switch(fork())
{
    case 0: //hijo - recibir
    close(fd[1]);
    break;
    
    default: //padre
    close(fd[0]);
    break;
    }
    return 0;
}