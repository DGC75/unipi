#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define UNIX_PATH_MAX 108
#define SOCKNAME  "./mysock"
#define N 100

//SERVER
int main (){
    //APRI CONNESSIONE E ASPETTA RICHIESTE
    //GESTIONE ERRORI!
    char buf[N] ={'\0'};
    char bufPrec[N] ={'\0'};
    char nullBuf[N] ={'\0'};

    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
        perror("err socket");

    struct sockaddr_un sa;
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);


    bind(sfd, (struct sockaddr *)&sa, sizeof(sa));
    listen(sfd, SOMAXCONN);
    int cfd;
    cfd = accept(sfd, NULL, 0);
    read(cfd, buf, N);

    while(strncmp("quit", buf, 5)!=0){

        printf("Server got %s\n", buf);


        
        write(sfd, nullBuf, N);
        memcpy(bufPrec, buf, N);
        while(memcmp(buf, bufPrec, N) == 0){
            read(cfd, buf, N);
            sleep(0.2);
        }
    }
    


    puts("Received quit");
    close(cfd);
    close(sfd);
    remove(SOCKNAME);
    return 0;
}