#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000


char* mystrcat1(char *s1, char *s2);
char* get_string(FILE *fPtr);

void mem_error();
void str_error();
void free_str(char** str);

int main(){

    char *str1 = get_string(stdin);
    char *str2 = get_string(stdin);
    char *str3 = mystrcat1(str1, str2);
    
    printf("%s", str3);
    
    free_str(&str1);
    free_str(&str2);
    free_str(&str3); 
    
    return 0;        
}

char* mystrcat1(char *s1, char *s2){
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char* new_str = calloc(len1 + len2, sizeof(char)); 
    if(new_str == NULL)
        mem_error();
    
    memcpy(new_str, s1, len1);
    memcpy((new_str + len1 -1), s2, len2);
    
    return new_str;    
}

char* get_string(FILE *fPtr){

    char* my_str = calloc(MAX_LENGTH + 1, sizeof(char));
    if(my_str == NULL)
        mem_error();
        
    if(fgets(my_str, MAX_LENGTH + 1, fPtr) == NULL)
        str_error();
    
    
    
    return my_str;    
}

void free_str(char** str){
    if(str != NULL && *str != NULL){
        free(*str);
        *str = NULL;
    }    
}

/*FUNZIONI DI ERRORE*/

void mem_error(){

    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}

void str_error(){

    puts("errore durante acquisizione stringa.");
    exit(EXIT_FAILURE);
}
