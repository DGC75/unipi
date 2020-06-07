#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*JUST A TEST*/

int main(){
    
    srand(time(NULL));
    printf("Usage: n a b\n");
    printf("n interi sull'intervallo [a b]\n");
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    int i;
    printf("%d\n\n", n);
    for(i = 0; i < n; i++){
        printf("%.0f\n", pow(-1, i)*(a + rand()%(b - a + 1)) );    
    }
}