#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ourhdr.h>

int main(void){
    pid_t pid;
    char buff[50];
    int p[2];
    char caratteritot[50];
    int num;

    if((pipe(p)) < 0){
        err_sys("Pipe error");
    }

    if((pid = fork()) < 0){
        err_sys("Fork error");
    }else if (pid > 0){ //padre

        close(p[0]);
        sprintf(buff, "ciao peppe\n");
        if(write(p[1], buff, strlen(buff)) < 0){
            err_sys("Padre error");
        }
        close(p[1);
        wait(NULL);
        
    } else{ //figlio
        close(p[1]);
        if((num = (read(p[0], buff, sizeof(buff)))) < 0){
            err_sys("Figlio error");
        }
        write(STDOUT_FILENO, buff, strlen(buff));

        sprintf(caratteritot,"numeri totali: %d\n", num);
        write(STDOUT_FILENO, caratteritot, strlen(caratteritot));
        close(p[0]);
    }

    exit(0);
}
