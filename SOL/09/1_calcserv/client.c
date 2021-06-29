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

static void run_server(struct sockaddr * sa){

	int fd_skt, fd_c;
	char msg[MAX_MSG_LEN] = {'\0'};
	printf("Server attivo: %d.\n", getpid());
	fflush(stdout);

	//APRI SOCKET E ASSEGNA INDIRIZZO
	fd_skt = socket(AF_UNIX, SOCK_STREAM,0);
	bind(fd_skt, sa, sizeof(*sa));

	////FORKA CALCOLATRICE E COLLEGALA CON PIPE
	int pidc;
	int frombc[2];
	int tobc[2];
	if(pipe(tobc) == -1){ perror("error pipe_tobc"); exit(EXIT_FAILURE);}
	if(pipe(frombc) == -1){ perror("error pipe_frombc"); exit(EXIT_FAILURE);}
	if((pidc = fork()) == -1){ perror("fork err"); exit(EXIT_FAILURE);}
	if(pidc == 0){
			puts("forking bc");
			close(frombc[0]);
			close(tobc[1]);
			dup2(tobc[0], 0);
            dup2(frombc[1], 1);
            dup2(frombc[1], 2);
			
            execlp("bc","bc", "-lq", (char*)NULL);
            puts("you shouldn't be here");
            exit(EXIT_FAILURE);
	}
	close(frombc[1]);
	close(tobc[0]);
	while(1){

		//ASCOLTA PER CONNESSIONI
        listen(fd_skt,0);
		//ACCETTA CONNESSIONE
        fd_c=accept(fd_skt,NULL,0);

		while(read(fd_c, msg, MAX_MSG_LEN)){
			//printf("server:ricevuto dal client:%s", msg);
			
			//INOLTRA MESSAGGIO ALLA CALCOLATRICE (PIPE)
			//puts("server:inoltro alla calc, attesa risposta...");
			write(tobc[1], msg, strlen(msg));
			//ASPETTA RISULTATO DALLA CALC
			memset(msg, '\0', MAX_MSG_LEN);
			read(frombc[0], msg, MAX_MSG_LEN);
			write(fd_c, msg, MAX_MSG_LEN);
			printf("server: ricevuto dalla calc:%s", msg);
			fflush(stdout);
			memset(msg, '\0', MAX_MSG_LEN);

			//MANDA RISULTATO AL CLIENT
			//puts("server:inoltro al client...");

		}
		close(fd_c);
		//CHIUDI CONNESSIONE 
	}
}
static void run_client(struct sockaddr * sa){
	printf("Client lanciato:%d\n", getpid());
	fflush(stdout);
	int fd_skt;
	char msg[MAX_MSG_LEN] = {'\0'};
	puts("client:aprendo connessione socket...");
	fd_skt=socket(AF_UNIX,SOCK_STREAM,0);
	while (connect(fd_skt,(struct sockaddr*)sa,sizeof(*sa)) == -1 ){
		if ( errno == ENOENT ) sleep(1); /* sock non esiste */
		else{
            perror("client connect");
            exit(EXIT_FAILURE);
        } 
	}
	puts("client: connessione socket accettata!");
	while(1){
		memset(msg, '\0', MAX_MSG_LEN);
		//RACCOGLI MESSAGGIO UTENTE
		fgets(msg, MAX_MSG_LEN, stdin);
		//SE QUIT, ESCI
		if(strncmp(msg, "quit\n", sizeof("quit\n")) == 0){
			puts("client: received quit");
			puts("client:closing connection...");
			close(fd_skt);
			puts("client: connection closed. Exiting.");
			break;
		}
		//MANDALO AL SERVER
		 write(fd_skt, msg, MAX_MSG_LEN);
		//ASPETTA RISULTATO 
		memset(msg, '\0', MAX_MSG_LEN);
	
		read(fd_skt, msg, MAX_MSG_LEN);
		printf("result:%s\n", msg);

	}
    puts("client:closing socket connection");
    close(fd_skt);
	return;
}


int main(void) {

	struct sockaddr_un sa; /* ind AF_UNIX */
	strcpy(sa.sun_path, SOCKNAME);
	sa.sun_family=AF_UNIX;	
    
    run_client((struct sockaddr *)&sa);/* attiv client*/ 
    return 0;
}
