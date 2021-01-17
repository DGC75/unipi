#include <stdio.h>

extern int call_me(int x);

int main (){
    puts("qui");
    int x = call_me(25);
    puts("quo");
    printf("%d\n", x);
    return 0;
}