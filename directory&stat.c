#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    DIR *dir; //puntatore a dir
    struct dirent *d; //struct che gestisce le dir
    struct stat s;  //struct per stampare i metadati

    if((dir = opendir(argv[1])) == NULL){  //devi passare la path della dir come argomento
        err_sys("opendir err");
    }
    
    while ((d = readdir(dir)) != NULL)  //Se è null è finito o errore
    {
        if(d->d_type == DT_REG){ //DT_DIR per le cartelle
            
            printf("nome: %s\n", d->d_name);
            stat(d->d_name, &s);
            printf("INO: %lu\n", s.st_ino);
            printf("Date: %s",ctime(&s.st_atime));
            printf("block: %lu\n", s.st_blocks);
            printf("block size: %lu\n\n", s.st_blksize);
        
        }
    }
    
    exit(0);
}
