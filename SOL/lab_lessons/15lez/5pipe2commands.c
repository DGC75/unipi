#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <x86_64-linux-gnu/bits/posix1_lim.h>

//SE HAI VOGLIA DI FARLO, FALLO...

 #define N 40
int main(int argc, char* argv[]){
    int pfd[2]; //This is an unnamed pipe
    //0 lettura 
    //1 scrittura
    int pid1, pid2;

    if(pipe(pfd) == -1){perror("pipe");}

    switch ((pid1 == fork()))
    {
    case -1:
        perror("fork pid1");
        exit(EXIT_FAILURE);
        break;
    
    default:
        break;
    }
    
    return 0;
}