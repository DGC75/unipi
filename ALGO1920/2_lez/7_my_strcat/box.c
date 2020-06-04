#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

char* mystrcat(char *s1, char *s2);
char* get_string(FILE *fPtr, int max_len);


void mem_error();
void str_err();

void free_str(char** strPtr);

int main(){
    
    char *str1 = get_string(stdin, MAX_LENGTH*2);
    char *str2 = get_string(stdin, MAX_LENGTH);
    
    printf("%s\n", mystrcat(str1, str2));
    
    free_str(&str1);
    free_str(&str2);
    
    return 0;
}

char* mystrcat(char *s1, char *s2){

    memcpy(s1 + strlen(s1),s2,strlen(s2) + 1);
    return s1;
}

char* get_string(FILE *fPtr, int max_len){

     char* new_str = calloc(max_len + 1, sizeof(char));
     
     if(new_str == NULL)
        mem_error();
    
    if(fgets(new_str, max_len + 1, fPtr) == NULL)
        str_err();
    
    new_str[strlen(new_str) - 1] = '\0';
    
    return new_str;
}

void free_str(char** strPtr){
    if(strPtr != NULL && *strPtr != NULL){
        free(*strPtr);
        *strPtr = NULL;
    }
}

void mem_error(){
    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}

void str_err(){
    puts("errore nell'acquisizione stringa'.");
    exit(EXIT_FAILURE);
}
