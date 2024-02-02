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

    //pid = fork();

    char buff[100];
    
    int fd = open("file.txt", O_RDWR|O_CREAT|O_TRUNC);

    sprintf(buff, "ciao peppe");
    write(fd, buff, strlen(buff));
    
    //LSEEK
    int x = lseek(fd, strlen(buff), SEEK_SET);

    if(x < 0){  //fd, ld spostamento, da dove parti   
        err_sys("lseek error");
    }else{
        printf("%d\n", x);
    }


    //BUCHI NEI FILE

    exit(0);
}

/*       
    SEEK_SET
              The file offset is set to offset bytes.

    SEEK_CUR
              The file offset is set to its current location plus offset bytes.

    SEEK_END
              The file offset is set to the size of the file plus offset bytes.
*/
