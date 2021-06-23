#include <stdio.h>
#include <unistd.h> 

int main(void){
    int pfd[2];

    if(pipe(pfd) == -1)
        perror("pipe");
    //MAXIMUM SIZE OF BYTES THAT CAN BE WRITTEN ATOMICALLY TO A PIPE OR FIFO.
    long sizew = fpathconf(pfd[0], _PC_PIPE_BUF);
    printf("%li bytes\n", sizew);

}