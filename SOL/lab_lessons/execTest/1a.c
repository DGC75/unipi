#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>




int main (int argc, char *argv[]){
    
    printf("Questa frase verra continuata ...");
    fflush(stdout);
    execl("/bin/echo","echo", "da", "me!", (char*) NULL);
    /*
    *p = path in cui cercare i comandi
    *v = vettore di argomenti stile argv
    *e = setting dell'environment
    *l = list argument, terminato da null
    */

   
    return 0;
}