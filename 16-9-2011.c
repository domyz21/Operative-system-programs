#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

/*
- Il processo padre apre 2 pipe e crea un processo figlio
- Il padre apre un file e legge riga per riga il contenuto inviando la riga letta al processo figlio
- Il figlio elimina tutte le vocali dalla linea letta dalla pipe e invia la stringa risultante al padre
- Il padre stampa la stringa ricevuta e legge la prossima linea del file
- Il padre quando arriva all'EOF manda la stinga "%%%" e aspetta che il figlio termina
- Il figlio una volta che riceve la stringa chiude le pipe e termina restituendo al padre il numero di vocali rimosse
*/

int main(void)
{
    pid_t A;
    int p[2][2];
    char buff[100];
    char new[100];
    int fd = open("file.txt", O_RDWR|O_CREAT);
    int numVoc = 0;
    int cont = 0;

    FILE *f = fdopen(fd, "rw");
    
    char flag[] = "%%%";

    for (int i = 0; i < 2; i++)
    {
        if(pipe(p[i]) < 0){
            err_sys("pipe err");
        }
    }



    if ((A = fork()) > 0) //parent
    {
        close(p[0][0]);
        close(p[1][1]);

        while(fgets(buff, sizeof(buff), f) != NULL){ //restituisce null quando finisce il file
        
            if(write(p[0][1], buff, strlen(buff)+1) < 0){
                err_sys("write err");
            }

            if(read(p[1][0], new, sizeof(new)) < 0){
                err_sys("read new err");
            }

            if(write(STDOUT_FILENO, new, strlen(new)+1) < 0){
                err_sys("Print err");
            }
            //memset(buff, '\0', strlen(buff));
            //memset(new, '\0', strlen(new));
        }
        
        if(write(p[0][1], flag, strlen(flag)+1) < 0){
            err_sys("Percent err");
        }


        if(read(p[1][0], &numVoc, sizeof(int)) < 0){
            err_sys("read numVoc err");
        } 

        printf("%d\n", numVoc);


        close(p[0][1]);
        close(p[1][0]);
        wait(NULL);
    }
    else if (A == 0) //child
    {
        close(p[0][1]);
        close(p[1][0]);

        while (1)
        {
            if(read(p[0][0], buff, sizeof(buff)) < 0){
                err_sys("read err");
            }
           
            if(strcmp(buff, flag) == 0)
                break;
            
        
            for(int i = 0; i < strlen(buff); i++){
                switch (buff[i])
                {
                case 'a': numVoc++ ;
                    break;

                case 'e': numVoc++;
                    break;

                case 'i': numVoc++;
                    break;
                    
                case 'o': numVoc++;
                    break;
                
                case 'u': numVoc++;
                    break;
                
                default:
                    new[cont] = buff[i];
                    cont++;
                }
            }
            new[cont] = '\0';

            if(write(p[1][1], new, strlen(new)+1) < 0){
                err_sys("write numVoc err");
            }

        }

        
        
        close(p[0][0]);

        if(write(p[1][1], &numVoc, sizeof(int)) < 0){
            err_sys("write new err");
        } 

        close(p[1][1]);

        printf("%d\n", numVoc);

    }
    else{
        err_sys("fork err");
    }
    
    


    exit(0);
}
