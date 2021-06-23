#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <wait.h>

#include <string.h>

#define MAX_STR _POSIX_PIPE_BUF

int main(void){
    int pfd[2];
    int pid;
    
    if(pipe(pfd) == -1){ perror("error pipe"); exit(EXIT_FAILURE);};

    char str[MAX_STR] = "\0";
    fgets(str, MAX_STR, stdin);

    while(strncmp("quit\n", str, 5)){
        
        switch (pid = fork())
        {
        case -1: perror("fork -1"); break;
        case 0: /*FIGLIO, LEGGE*/ 
            

            read(pfd[0], str, MAX_STR);
            printf("received:%s\n", str);
            memset(str, 0, MAX_STR);
            close(pfd[0]);
            break;

        default: /*PADRE, SCRIVE*/  
            close(pfd[0]);
            write(pfd[1], str, MAX_STR);
            break;
        }

        fgets(str, MAX_STR, stdin);
    }

    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid,NULL,0);

    return 0;
}