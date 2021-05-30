#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h> 
#include <dirent.h>      
#include <sys/stat.h>

#include <time.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 512

void print_attr(char *pathname);

int main(int argc, char *argv[]){

    char buf[BUF_SIZE] = ""; 
    if(getcwd(buf, BUF_SIZE) == NULL){
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    if(chdir(argv[1]) == -1){
        perror("chdir");
        exit(EXIT_FAILURE);
    }



    DIR* dir = opendir(argv[1]);
    if(dir == NULL){
        perror("dir == NULL");
        exit(EXIT_FAILURE);
    }

    struct dirent* file; 
    errno = 0;

    while( errno = 0 , (file = readdir(dir)) != NULL ){
        print_attr(file->d_name);
    }

    if(closedir(dir) == -1){
        perror("error closing dir");
        exit(EXIT_FAILURE);
    }

    if(chdir(buf) == -1){
        perror("err returning to main dir");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

void print_attr(char * path){
    printf("path:%s\n", path);
    struct stat info;
    if ( stat(path,&info)== -1){
        /* gestione errore */
    } else {
            printf("Attributi %s:\n",path); 
            /* nome file */printf("tipo: "); /* stampa il tipo */
            if (S_ISREG(info.st_mode)) printf("regular");
            else if (S_ISDIR(info.st_mode)) printf("directory"); 
            else if (S_ISLNK(info.st_mode)) printf("link simb");
            else if (S_ISCHR(info.st_mode)) printf("character special file");
            else if (S_ISBLK(info.st_mode)) printf("block special file");
            else if (S_ISFIFO(info.st_mode)) printf("pipe");
            else if (S_ISSOCK(info.st_mode)) printf("socket");
            else
                printf("non riconosciuto");

        /* stampa il numero di i-node */
        printf("\ni node number %ld ", (long)info.st_ino);
        /* stampa il modo (formato rw---x--x) *//* user */
        if (S_IRUSR & info.st_mode) putchar('r'); else putchar('-');
        if (S_IWUSR & info.st_mode) putchar('w'); else putchar('-');
        if (S_IXUSR & info.st_mode) putchar('x'); else putchar('-');/* group */
        if (S_IRGRP & info.st_mode) putchar('r'); else putchar('-');
        if (S_IWGRP & info.st_mode) putchar('w'); else putchar('-');

        /* continua group */
        if (S_IXGRP & info.st_mode) putchar('x');else putchar('-');
        /* others */
        if (S_IROTH & info.st_mode) putchar('r');else putchar('-');
        if (S_IWOTH & info.st_mode) putchar('w');else putchar('-');
        if (S_IXOTH & info.st_mode) putchar('x');else putchar('-');
        /* ultimo accesso */
        printf("\nultima modifica: %s",ctime(&info.st_mtime)); 

        /* stampa uid, gid numerico */
        printf("uid %d\n", info.st_uid);
        printf("gid %d\n", info.st_gid);

        puts("");
    }
}