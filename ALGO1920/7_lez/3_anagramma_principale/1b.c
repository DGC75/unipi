#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define REAL_LENGTH 21


int char_cmp(const void *a, const void *b);
int str_cmp(const void *a, const void *b);
int ap(char *a, char *b);


int main(){
    /*LEGGI N*/
    
    int N;
    scanf("%d", &N);
    scanf("%*c");
    /*ACQUISISCI N STRINGHE*/
    char **str_arr = calloc(N, sizeof(char*));

    int i;
    for(i = 0; i < N; i++){
        
        str_arr[i] = calloc(REAL_LENGTH, sizeof(char));
        
        
        fgets( *(str_arr + i), REAL_LENGTH, stdin);

        
        *(*(str_arr + i) + strlen(*(str_arr + i)) - 1) = '\0';
    }
           
    /*ORDINA TUTTO L'ARRAY PER ANAGRAMMA PRINCIPALE*/
    /*A PARITA DI ANAGRAMMA PRINCIPALE, ORDINA PER ORDINE LESSICOGRAFICO DELLA STRINGA*/
    qsort(str_arr, N, sizeof(char*), str_cmp);
    
    /*STAMPA:*/
    
    /*PER OGNI STRINGA, STAMPALA SEGUITA DA SPAZIO.*/ 
    /*SE LA STRINGA SUCCESSIVA E' DIVERSA DALLA CORRENTE(O NON ESISTE), STAMPA \n */
    for(i = 1; i < N; i++){
        if(ap(str_arr[i - 1], str_arr[i]) != 0){
            printf("%s\n", str_arr[i - 1]);
        }else
            printf("%s ", str_arr[i - 1]);
        
    }
    printf("%s", str_arr[i - 1]);
}

int str_cmp(const void *a, const void *b){
    
    char **str1 = (char **) (a); 
    char **str2 = (char **) (b); 

    int ap_cmp = ap(*str1, *str2);
    
    if( ap_cmp != 0)
        return ap_cmp;
    else
        return strcmp(*str1, *str2);
}

int ap(char *a, char *b){
    
    /*ANAGRAMMA PRINCIPALE: COPIA STRINGA, RIORDINO E CONFRONTO, LIBERO STRINGHE*/
    
    char *str1 = calloc(REAL_LENGTH, sizeof(char));
    
    memcpy(str1, a, REAL_LENGTH);

    char *str2 = calloc(REAL_LENGTH, sizeof(char));
    

    memcpy(str2, b, REAL_LENGTH);

    qsort(str1, strlen(str1), sizeof(char), char_cmp);
    qsort(str2, strlen(str2), sizeof(char), char_cmp);

    return strcmp(str1, str2);
}



int char_cmp(const void *a, const void *b){    
    return (int)(*((char *) (a))) - (int)(*((char *) (b))); 
}