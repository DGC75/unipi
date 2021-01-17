#include <stdio.h>

extern int IP(int*x, int*y, int n);

int main(){

    int x[] ={1,2,3,4};
    int y[] ={1,2,3,4};

    printf("print:%d\n",IP(x,y,4));
}