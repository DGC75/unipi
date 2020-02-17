#include <stdio.h>
#include <stdlib.h>

#define CHAR_RANGE 256 

void str_error();
void mem_error();

unsigned char* get_string(FILE *fPtr);
int anagramma(unsigned char *s1, unsigned char *s2);

void conta_occorrenze(int arr[], size_t dim, unsigned char *str);
int  corrispondenza_tabelle(int arr1[], int arr2[], size_t dim);

int main(){
	
	unsigned char *str1, *str2;

	str1 = get_string(stdin);
	str2 = get_string(stdin);

	printf("%d\n", anagramma(str1, str2));

}

int anagramma(unsigned char *s1, unsigned char *s2){
	
	int c_arr_s1[CHAR_RANGE] = {0};
	int c_arr_s2[CHAR_RANGE] = {0};

	conta_occorrenze(c_arr_s1, CHAR_RANGE, s1);
	conta_occorrenze(c_arr_s2, CHAR_RANGE, s2);

	return corrispondenza_tabelle(c_arr_s1, c_arr_s2, CHAR_RANGE);
}

void conta_occorrenze(int arr[], size_t dim, unsigned char *str){
	
	int i = 0;
	while(str[i] != '\0'){
		arr[str[i]]++;
		i++;
	}
}

int corrispondenza_tabelle(int arr1[], int arr2[], size_t dim){
	int i;
	for(i = 0; i < dim; ++i){
		if(arr1[i] != arr2[i])
			return 0;
	}
	return 1;	
}

unsigned char* get_string(FILE *fPtr){

	fpos_t start;
	int dim = 0;
	fgetpos(fPtr, &start);
	while(!feof(fPtr) && fgetc(fPtr) != '\n')
		dim++;
	fsetpos(fPtr, &start);

	unsigned char* tmp = calloc(dim+1, sizeof(unsigned char));

	if(tmp == NULL)
		mem_error();

	if(fgets((char*) tmp, dim+1, fPtr) == NULL)
		str_error();

	fgetc(fPtr);
	return tmp;	
}

void mem_error(){
	puts("memoria esaurita.");
	exit(EXIT_FAILURE);
}

void str_error(){
	puts("errore durante l'acquisizone della stringa.");
	exit(EXIT_FAILURE);
}