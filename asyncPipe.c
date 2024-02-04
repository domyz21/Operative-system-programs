#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
/*
tremite una pipe asincrona (non bloccante), il figlio, con una probabilità di 9/10 manda un messaggio al padre (un numero)
con un altra probabilità di 1/10 il figlio termina.
il padre deve controllare periodicamente la pipe
*/
int main(void)
{

    pid_t pid;
    int p[2];
    char buff[100];

    pipe2(p, O_NONBLOCK);  //pipe non bloccanti


    if((pid = fork()) > 0){ //parent
     
        close(p[1]);
        
        while(1){
            int x = 0;
            int status;
            if((status = read(p[0], &x, sizeof(x))) > 0){

                sprintf(buff, "Numero uscito: %d\n", x);
            
                write(STDOUT_FILENO, buff, strlen(buff));
            
            }else if (status < 0 && errno != EAGAIN || errno != EWOULDBLOCK){
                err_sys("read err");
            }else if(status == 0){
                printf("Padre ha finito\n");
                break;
            }

            usleep(500);
        }

        close(p[0]);

    }else if(pid == 0){ //child

        close(p[0]);
        
        srandom(time(NULL));

        while(1)
        {
            int ran = random()%10;

            if(ran != 0){
                if((write(p[1], &ran, sizeof(ran))) < 0){
                    err_sys("Write err");
                }
            }else{
                printf("Figlio ha termianto\n");
                break;
            }

            usleep(500);
        }

        close(p[1]);

    }else{
        err_sys("pipe err");
    }

    exit(0);
}
