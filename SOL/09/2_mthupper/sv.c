#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h> 
#include <limits.h>

#include <assert.h>

#define SOCKNAME "./mysock"
#define MAX_MSG_LEN _POSIX_PIPE_BUF

#define EX_IFVAL(fun, var, val, error_str, exit_value) \
        if((var = fun) == val){\
            perror(error_str);\
            exit(exit_value);\
        }

#define EX_IFNOTVAL(fun, var, val, error_str, exit_value) \
        if((var = fun) != val){\
            perror(error_str);\
            exit(exit_value);\
        }



void launch_new_thread(int fdc){
    //LAUNCH DETACHED THREAD
    //READ FROM fdc
        //IF(READ RETURNS 0, CLOSE fdc AND EXIT)
    //UPSTRING
    //WRITE TO fdc
}

void run_server(struct sockaddr * sa){
    
    int fdc, sfd;
    int err;
    //UNLINKA SOCKET
    EX_IFNOTVAL(unlink(SOCKNAME), err, 0, "unlink", err);
    
    //SOCKET
    EX_IFVAL(socket(AF_UNIX, SOCK_STREAM,0), sfd, -1, "socket", EXIT_FAILURE);

    //BIND
    EX_IFVAL(bind(sfd, sa, sizeof(*sa)), err, -1, "bind", EXIT_FAILURE);

    //LISTEN(SOMAXCONN)
    EX_IFVAL(listen(sfd, SOMAXCONN), err, -1, "listen", EXIT_FAILURE);

    while(1){
        //ACCEPT
        
        //CREA NUOVO THREAD IN DETACHED
        launch_new__thread(fdc);
    }
}


int main(void) {
	struct sockaddr_un sa; /* ind AF_UNIX */
	strcpy(sa.sun_path, SOCKNAME);
	sa.sun_family=AF_UNIX;
    run_server((struct sockaddr *)&sa);/* attiv server */
    return 0;
}