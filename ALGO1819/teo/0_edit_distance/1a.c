#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

int edit_distance(char *x_str, char *y_str);
char* get_string();
int min(int x1, int x2, int x3);

int main(){
    char *x = get_string();
    char *y = get_string();

    printf("%d\n", edit_distance(x, y));

    return 0;
}


int edit_distance(char *x_str, char *y_str){
    
    int n = strlen(x_str), m = strlen(y_str);
    printf("n : %d, m : %d\n", n, m);
    int **matr= calloc(n + 1, sizeof(int*));
    
    int i, j, p;
    for(i = 0; i < n + 1; i++)
        matr[i] = calloc(m + 1, sizeof(int));

    
    /*INIT*/
    for(i = 0; i < n + 1; i++)
    matr[i][0] = i;

    for(i = 1; i < m + 1; i++)
        matr[0][i] = i;
    puts("qui");

    /*SOTTOPROBLEMI*/
    for(i = 1; i < n + 1; i++){
        for(j = 1; j < m + 1; j++){
            
            if(x_str[i] == y_str[j])
                p = 0;
            else
                p = 1;
            
            printf("1: %d %d\n", i, j);
            matr[i][j] = min(matr[i-1][j-1] + p, matr[i -1][j] + 1, matr[i][j - 1] + 1);
            printf("2: %d %d\n", i, j);
            
        }
    }

    return matr[n][m];
}

int min(int x1, int x2, int x3){
    if(x1 <= x2){
        if(x1<= x3)
            return x1;
        else
            return x3;
    }
    else{
        if(x2 <= x3)
            return x2;
        else
            return x3;
    }
}

char* get_string(){
    
    char *str = calloc(MAX_STR_LEN + 1, sizeof(char));

    fgets(str, MAX_STR_LEN + 1, stdin);
    str[strlen(str) - 1] = '\0';
    return str;
}