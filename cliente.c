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
    char orden[20] ="mkfifo ";
    
    fdw = open("servidor",O_WRONLY);
    if(fdr ==-1)
    {
            perror("");
        exit(1);

    }
    printf("nombre");
    scanf("%s", info.nombre);
    strcat(orden,info.nombre);
    system(orden);
    do{
        printf("opcion");
        scanf("%d", &info.opc);

        write(fdw,&info, sizeof(info));
        fdr = open(info.nombre, O_RDONLY);
        read(fdr, &info, sizeof(info));
        printf("%s\n",info.respuesta);
        close(fdr);
    }
    while(1);
    
    return 0;
}