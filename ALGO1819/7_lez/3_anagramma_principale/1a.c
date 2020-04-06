#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_LENGTH  20
#define REAL_LENGTH (MAX_LENGTH + 1)

void mem_err();
void err();

int char_cmp(const void *a, const void *b);
int str_cmp(const void *a, const void *b);
int ap(char *a, char *b);


int main(){
    /*LEGGI N*/
    
    int N;
    scanf("%d", &N);
    scanf("%*[^\n]");
    scanf("%*c");
    /*ACQUISISCI N STRINGHE*/
    char **str_arr = calloc(N, sizeof(char*));
    if(str_arr == NULL)
        mem_err();


    int i;
    for(i = 0; i < N; i++){
        
        str_arr[i] = calloc(REAL_LENGTH, sizeof(char));
        
        if(str_arr[i] == NULL)
            mem_err();
        
        if(fgets( *(str_arr + i), REAL_LENGTH, stdin) == NULL)
            err();
        
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

    /*FREE DELLE STRUTTURE ALLOCATE*/
    for(i = 0; i < N; i++){
        free(str_arr[i]);
        str_arr[i] = NULL;
    }

    free(str_arr);
    str_arr = NULL;    
    
}

int str_cmp(const void *a, const void *b){
    
    char **str1 = (char **) (a); 
    char **str2 = (char **) (b); 

    int ap_cmp = ap(*str1, *str2);
    
    if( ap_cmp < 0)
        return -1;
    else if(ap_cmp > 0)
        return 1;
    else
        return strcmp(*str1, *str2);
}

int ap(char *a, char *b){
    
    /*ANAGRAMMA PRINCIPALE: COPIA STRINGA, RIORDINO E CONFRONTO, LIBERO STRINGHE*/
    
    char *str1 = calloc(REAL_LENGTH, sizeof(char));
    
    if(str1 == NULL)
        mem_err();

    memcpy(str1, a, REAL_LENGTH);

    char *str2 = calloc(REAL_LENGTH, sizeof(char));
    
    if(str2 == NULL)
        mem_err();

    memcpy(str2, b, REAL_LENGTH);

    qsort(str1, strlen(str1), sizeof(char), char_cmp);
    qsort(str2, strlen(str2), sizeof(char), char_cmp);

    int result = strcmp(str1, str2);
    
    free(str1);
    str1 = NULL;

    free(str2);
    str2 = NULL;

    return result;
}


void mem_err(){
    puts("memoria heap esaurita.");
    exit(EXIT_FAILURE);
}

void err(){
    puts("qualcosa e' andato storto");
    exit(EXIT_FAILURE);
}

int char_cmp(const void *a, const void *b){

    char *c1 = (char *) (a);
    char *c2 = (char *) (b);
    
    return (int)(*c1) - (int)(*c2); 
}