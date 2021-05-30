#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>




int main (int argc, char *argv[]){
    //OTTENIAMO IL PID DEL PROCESSO ATTUALE
    pid_t me_pid = getpid();
    //OTTENIAMO IL PID DEL PADRE
    pid_t parent_pid = getppid();

    printf("me:\t%d\n", me_pid);
    printf("parent:\t%d\n", parent_pid);

    //FORK: CREA NUOVI PROCESSI
    pid_t pid_newProc = fork();
    if(pid_newProc == -1){
        perror("non sono riuscito a forkare un nuovo processo");
        exit(EXIT_FAILURE);
    }

    printf("%d: ho ricevuto %d\n", getpid(), pid_newProc);
    //I DUE PROCESSI HANNO LO STESSO SPAZIO DI INDIRIZZAMENTO
    return 0;
}