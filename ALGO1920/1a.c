#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int();
void mem_err();

int main(){


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