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


void run_client(struct sockaddr * sa){
    
}


int main(void) {
	struct sockaddr_un sa; /* ind AF_UNIX */
	strcpy(sa.sun_path, SOCKNAME);
	sa.sun_family=AF_UNIX;
    run_client((struct sockaddr *)&sa);/* attiv server */
    return 0;
}