#include <stdio.h>
#include <string.h>
#include <ourhdr.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>


int wrong = 0, right = 0;
int lastchar = 0;

void handler(int sig){
    if(lastchar == 0){
        wrong++;
    }else if(lastchar == 1){
        right++;
    }
}

int main(void)
{

    srandom(time(NULL));
    int r;

    if(signal(SIGINT, handler) == SIG_ERR){
        err_sys("Signal err");
    }

    for(int i = 0; i < 10; i++){

        if((r = random()%10) == 0){
            write(STDOUT_FILENO, "0", strlen("0"));
            lastchar = 1;
        }   
        else{
            write(STDOUT_FILENO, "_", strlen("_"));
            lastchar = 0;
        }

        sleep(1); 
    }
    
    printf("\nPunti: %d\nPunti persi: %d\n", right, wrong);

    exit(0);
}
