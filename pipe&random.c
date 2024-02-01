#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{

    pid_t pid;
    char buff[100];
    char *vett[] = {"ls", NULL};
    int Pipe[2];

    pipe(Pipe);

    if ((pid = fork()) > 0)
    { // padre
        close(Pipe[0]);

        sprintf(buff, "Ciao figlio\n");

        srandom(time(NULL));
        int r = random() % 2;

        if (r == 1)
        {
            if ((write(Pipe[1], buff, strlen(buff))) < 0)
            {
                err_sys("Write error");
            }
        }

        close(Pipe[1]);
        wait(NULL);
    }
    else if (pid == 0)
    { // figlio
        close(Pipe[1]);
        int res = read(Pipe[0], buff, sizeof(buff));
        if (res < 0)
        {
            err_sys("Read error");
        } else if (res == 0){
            execve("/usr/bin/ls", vett, NULL);
        } else{
            write(STDOUT_FILENO, buff, strlen(buff));
        }
        
        close(Pipe[0]);

    }
    else
    {
        err_sys("Fork error");
    }

    exit(0);
}

// probab 1-2 invia un mess al figlio e se il figlio riceve stampa altrimenti esegue ls
