#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100


void mem_err();
int get_int();



int main(){
    /*Just a test*/
    return 0;
}

int get_int(){
    int tmp;
    scanf("%d", &tmp);
    scanf("%*[^\n]");
    scanf("%*c");

    return tmp;
}

void mem_err(){
    puts("memoria heap esaurita");
    exit(EXIT_FAILURE);
}
