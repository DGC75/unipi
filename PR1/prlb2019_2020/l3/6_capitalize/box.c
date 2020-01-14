#include <stdio.h>
#include <ctype.h>

int main(void){
    char carattere=0;
    scanf("%c", &carattere);
    if (islower(carattere))
    {
        printf("%c\n",toupper(carattere));
    }else {
        printf("invalid input\n");
    }

}