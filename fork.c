#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <ourhdr.h>

int main(void) {
    char buff[100];
    pid_t pid;
    int status; //status di exit
    char arg[] = {"ls", "/", NULL}; //argomenti per l'execve

    pid = fork(); //crea una copia del processo padre

    if(pid > 0){ //siamo nel padre
        waitpid(pid, &status , 0); //pid del figlio ceh dobbiamo aspettare, status dell'exit
        printf("%d", WEXITSTATUS(status)); //stampa lo stato dell'exit, 0 se non ci sono problemi
    }else if(pid == 0){ //siamo nel figlio
        sprintf(buff, "Hello\n");
        write(STDOUT_FILENO, buff, strlen(buff)); //macro, buffer dove abbiamo scritto il mess, lunghezza buff tipo
        //write(STDOUT_FILENO, "ciao\n", size("ciao\n")); invece di fare SPRINTF e BUFF 
        sleep(1);
        execve("/usr/bin/ls", arg, NULL); //cerca path, argomenti = il comando da usare , null
        //tutto quello che c'è dopo non viene eseguito, a meno che non fallisce
    }else{
        err_sys("Fork error");
    }

    exit(0);
}
