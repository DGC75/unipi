#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

char* get_string(FILE *fPtr);
int mystrcmp(char* s1, char* s2);
void mem_error();
void str_error();


int main(){
    char *str1 = get_string(stdin);
    char *str2 = get_string(stdin);

    int output = mystrcmp(str1, str2);
    if(output != 0)
    	printf("%+d\n", output);
    else
    	puts("0");

    return 0;
}

char* get_string(FILE *fPtr){
	
	char* my_str = calloc(MAX_LENGTH+1, sizeof(char));
	if (my_str == NULL)
		mem_error();

	if(fgets(my_str, MAX_LENGTH+1, fPtr) == NULL)
		str_error();

	return my_str;
}

int mystrcmp(char* s1, char* s2){	

	int i = 0;
	while(s1[i] != '\0'){
		if (s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;
		else
			i++;
	}

	return 0;
}

void mem_error(){
	puts("Memoria esaurita.");
	exit(EXIT_FAILURE);
}
void str_error(){
	puts("Errore acquisizione stringa.");
	exit(EXIT_FAILURE);
}