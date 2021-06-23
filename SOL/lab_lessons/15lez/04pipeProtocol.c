#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <x86_64-linux-gnu/bits/posix1_lim.h>



 #define N 40
int main(int argc, char* argv[]){
    int pfd[2]; //This is an unnamed pipe
    //0 lettura 
    //1 scrittura
    int pid, l, k;
    char msg[N];

    if(pipe(pfd) == -1){perror("pipe");}

    if((pid = fork()) == -1){perror("fork");}

    //PARENT
    if(pid){
        int l,lung; 
        char* pmsg; 
        close(pfd[1]);

        l=read(pfd[0],&lung,sizeof(int));

        if(l==-1){perror("read lung");}
        assert(lung > 0);
        
        pmsg = malloc(lung);
        
        l=read(pfd[0],pmsg,lung);
        printf("%s\n",pmsg);  
        free(pmsg);
        close(pfd[0]);

    }
    else{//CHILD
        int lung;
        close(pfd[0]);
        snprintf(msg,N, argv[1],getpid());
        lung = strlen(msg) + 1;
        /* primo messaggio: lunghezza messaggio */
        k = write(pfd[1], &lung, sizeof(int));
        /* esito ... ... messaggio effettivo*/

        k = write(pfd[1],msg,lung);
        /* esito ... */
        close(pfd[1]);
    }

    return 0;
}