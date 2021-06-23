#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <x86_64-linux-gnu/bits/posix1_lim.h>

 #define N 20
int main(void){
    int pfd[2]; //This is an unnamed pipe
    //0 lettura 
    //1 scrittura
    int pid, l;
    char msg[N];

    if(pipe(pfd) == -1){perror("pipe");}

    if((pid = fork()) == -1){perror("fork");}


    //PARENT
    if(pid){
        close(pfd[1]);
        l = read(pfd[0], msg, N);
        if(l == -1){perror("read");}
        else printf("Msg received from child:\n%s\n", msg);
        
        close(pfd[0]);

    }
    else{
        close(pfd[0]);
        puts("Insert message:");
        scanf("%[^\n]", msg);
        scanf("%*c");
        l = write(pfd[1], msg, N);
        if(l == -1){perror("write");}

        close(pfd[1]);
    }

    return 0;
}