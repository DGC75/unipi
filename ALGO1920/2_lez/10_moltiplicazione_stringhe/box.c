#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

char*   product(char *str, int k);
char*   get_string(FILE *fPtr);
int     get_int(FILE *fPtr);     

void mem_err();
void str_err();

void free_str(char** str);

int main(){
	
	char* str = get_string(stdin);
    int n = get_int(stdin);

    char* output = product(str, n);
    
	printf("%s\n", output);
	
	free_str(&str);
	free_str(&output);
	
	return 0;
}

char* product(char *str, int k){
    
    int dim = strlen(str);
    
    char* new_str = calloc(k*dim + 1, sizeof(char));
    if(new_str == NULL)
        mem_err();
    
    int i;
    for(i = 0; i < k; ++i){
        memcpy(new_str + i*dim, str, dim);
    }
    
    new_str[k*dim] = '\0';        
    
    return new_str;
}
char* get_string(FILE *fPtr){

    char* new_str = calloc(MAX_LENGTH + 1, sizeof(char));
    
    if(new_str == NULL)
        mem_err();
        
    if(fgets(new_str, MAX_LENGTH + 1, fPtr) == NULL)
        str_err();
    
    new_str[strlen(new_str)-1] = '\0';
    
    return new_str;
}
int get_int(FILE *fPtr){
    
    int result;
    fscanf(fPtr, "%d\n", &result);
    
    return result;
}     

void mem_err(){
    puts("memoria esaurita.");
    exit(EXIT_FAILURE);
}
void str_err(){
    puts("errore durante acquisizione stringa.");
    exit(EXIT_FAILURE);
}

void free_str(char** str){
    if(str != NULL && *str != NULL)
        free(*str);
    
    *str = NULL;
}