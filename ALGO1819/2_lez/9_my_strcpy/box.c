#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

char* get_string(FILE *fPtr);
char* alloc_string(size_t dim);
char* mystrcpy(char* dest, char* src);

void mem_error();
void str_error();

int main(){
	
	char* str1 = get_string(stdin);
	char* str2 = alloc_string(MAX_LENGTH);


	printf("%s", mystrcpy(str2, str1));

	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
}

char* get_string(FILE *fPtr){
	
	char* new_str = alloc_string(MAX_LENGTH);

	if(fgets(new_str, MAX_LENGTH+1, fPtr) == NULL)
		str_error();

	return new_str;
}

char* alloc_string(size_t dim){
	char *new_str = calloc(dim+1, sizeof(char));

	if(new_str == NULL)
		mem_error();

	return new_str;
}

char* mystrcpy(char* dest, char* src){
	int i = 0;
	do{
		dest[i] = src[i];
		i++;
	}while(src[i] != '\0');

	return dest;
}

void mem_error(){
	puts("memoria esaurita.");
	exit(EXIT_FAILURE);
}
void str_error(){
	puts("errore durante acquisizione stringa.");
	exit(EXIT_FAILURE);
}