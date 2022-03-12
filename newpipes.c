#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd[2];

    if (pipe(fd) == -1){
        printf("Error abriendo el pipe");
        return 1;
    }
    int id = fork();
    if (id == 0){
        close(fd[0]);
        int x;
        printf("Imprime un número: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }

    else{
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Del proceso hijo: %d\n", y);
    }
}