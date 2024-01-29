#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(void){
    pid_t pid;
    int p[2];
    char buff[20];
    char *vett[5] = {"sbu\n", "sbora\n", "omicidio\n", "genocidio\n", "femminicidio\n"}; 
    
    if(pipe(p) < 0){
        err_sys("Pipe error");
    }
    
    if ((pid = fork()) < 0) 
    {
        err_sys("figlio aborto");
    }
    else if(pid > 0){ //padre

        close(p[1]);
        FILE *f = fdopen(p[0], "r"); 
        //trosforma un file descriptor in uno stream e ritorna un puntatore a file

        for (int i = 0; i<5; i++)
        {

            if ((fgets(buff, sizeof(buff), f)) == NULL)
            {
                err_sys("Errore read padre");
            }
            write(STDOUT_FILENO, buff, strlen(buff));
        }

        close(p[0]);
        wait(NULL);

    }else{ //figlio
        
        close(p[0]);
        for (int i = 0; i < 5; i++)
        {
            if(write(p[1], vett[i], strlen(vett[i])) < 0){
                err_sys("Errore write figlio");
            }    
        }
        close(p[1]);
        

    }
     
    
    exit(0);
}
