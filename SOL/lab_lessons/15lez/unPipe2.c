#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <x86_64-linux-gnu/bits/posix1_lim.h>

int main(void){
    int pfd[2]; //This is an unnamed pipe
    //0 lettura 
    //1 scrittura

    if(pipe(pfd) == -1){perror("pipe");};

    //PosixPipeBuf is the minimum size that is writable
    printf("POSIX = %d e ",_POSIX_PIPE_BUF);

    //Real MAX SIZE THAT can be written atomically to a pipe or fifo.
    errno = 0;
    long int v;
    if ((v = fpathconf(pfd[0],_PC_PIPE_BUF))==-1){
        if (errno != 0) {/* errore */}
        else printf("Reale = illimitato\n");
    }
    else
        printf("Reale: %li\n", v);
    
    return 0;
}