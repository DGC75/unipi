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

void run_client(struct sockaddr_un *sa);
void run_server(struct sockaddr_un *sa);

int main (int argc, char *argv[]){
    
    struct sockaddr_un sa;
    strcpy(sa.sun_path, SOCKNAME);
    sa.sun_family = AF_UNIX;

    int i;
    for(i = 0; i < 4; i++)
        run_client(&sa);

    run_server(&sa);

    return 0;
}

int aggiorna(fd_set * setP, int max_fd){
    //RESTITIUISCE IL PIU' GRANDE FD APPARTENENTE AL SET
    int i;
    int max = 0;

    for(i = max_fd; i >= 0; i--){
        if(FD_ISSET(i, setP)){
            return i;
        }
    }

    puts("non ci sono più descrittori aperti");
    return -1;
}

void run_client(struct sockaddr_un *sa){
    if(fork() == 0){
        int fdSock;
        char buf[N];

        fdSock = socket(AF_UNIX, SOCK_STREAM, 0);
        while(connect(fdSock, (struct sockaddr *)sa, sizeof(*sa)) == -1){
            if(errno == ENOENT)
                sleep(1);
            else
                exit(EXIT_FAILURE);

            write(fdSock, "Hello!", 7);
            read(fdSock, buf, N);
            printf("Client got:%s\n", buf);
            close(fdSock);
            exit(EXIT_SUCCESS);
        }
    }
}




void run_server(struct sockaddr_un *sa){
    int sock_conn;
    int sock_io;
    int max_fd = 0;
    int fd_index;

    char buf[N];

    fd_set set, rdset;
    int nread;

    sock_conn = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(sock_conn, (struct sockaddr *) sa, sizeof(sa));
    listen(sock_conn, SOMAXCONN);
    if(sock_conn > max_fd)
        max_fd = sock_conn;
    
    FD_ZERO(&set);
    FD_SET(sock_conn, &set);

    while(1){
        rdset = set;
        if(select(max_fd + 1, &rdset, NULL, NULL, NULL) == -1){
            perror("err select");
        }
        else{
            for(fd_index = 0; fd_index < max_fd; fd_index++){
                if(FD_ISSET(fd_index, &rdset)){
                    if(fd_index == sock_conn){
                        sock_io = accept(sock_conn, NULL, 0);
                        FD_SET(sock_io, &set);
                        if(sock_io > max_fd)
                            max_fd = sock_io;
                    }
                    else{
                        nread = read(fd_index, buf, N);
                        if(nread == 0){
                            FD_CLR(fd_index, &set);
                            max_fd = aggiorna(&set, max_fd);
                            close(fd_index);
                        }
                    }
                }
                else{
                    printf("Server got: %s\n", buf);
                    write(fd_index, "Bye!", 5);
                }


            }
        }
    }

}
