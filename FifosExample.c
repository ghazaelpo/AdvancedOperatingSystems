#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int i, pid, status;
    pid = fork();
    switch (pid)
    {
    case -1:
        /* An error has occurred */
        printf("Fork Error");
        break;
    case 0:
        /* This code is executed by the first parent */
        printf("First child process is born, my pid is %d\n", getpid());
        printf("First child parent process is %d\n", getppid());
        for (i = 1; i <= 10; i++)
            printf("First child process, iteration: %d\n", i);
        printf("First child dies quietly.\n");
        break;
    default:
        /* This code is executed by the parent process */
        printf("Parent process is born, my pid is %d\n", getpid());
        wait(&status);
        printf("Parent process dies quietly.\n");
    }
}