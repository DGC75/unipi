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

//SERVER
int main (void){
    
    int fd_skt, fd_c;
    char buf[N];

    struct sockaddr_un sa;

    strncpy(sa.sun_path, SOCKNAME,UNIX_PATH_MAX);    
    sa.sun_family=AF_UNIX;

    if(fork() != 0){
        fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        bind(fd_skt, (struct sockaddr *) &sa, sizeof(sa));
        listen(fd_skt, SOMAXCONN);
        fd_c = accept(fd_skt, NULL, 0);

        read(fd_c, buf, N);
        printf("Server got: %s\n", buf);
        write(fd_c, "Bye!", 5);
        close(fd_skt);
        close(fd_c);
        exit(EXIT_SUCCESS);

    }
    else{
        fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        while((connect(fd_skt, (struct sockaddr *) &sa, sizeof(sa))) == -1){
            if(errno == ENOENT)
                sleep(1);
            else
                exit(EXIT_FAILURE);
        }
        write(fd_skt, "Halo!", 5);
        read(fd_skt, buf, N);

        printf("Client got: %s\n", buf);
        close(fd_skt);
        exit(EXIT_SUCCESS);

    }
  
}