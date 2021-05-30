#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define UNIX_PATH_MAX 108
#define SOCKNAME  "./mysock"
#define N 100


//CLIENT
int main (int argc, char *argv[]){
    
    char buf[N] ={'\0'};
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
        perror("err socket");

    struct sockaddr_un sa;
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);

    if((connect(sfd, (struct sockaddr *)&sa, sizeof(sa))) ==-1)
        perror("err connect");

    do{
        memset(buf, '\0', N);
        scanf("%s[^\n]", buf);
        scanf("%*c");
        write(sfd, buf, N);
        

    }while(strcmp(buf, "quit"));
    
    close(sfd);
    return 0;
}