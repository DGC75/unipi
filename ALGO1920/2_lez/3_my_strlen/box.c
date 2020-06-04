#include <stdio.h>

int mystrlen(char *s);

int main(){

	int dim = 0;

	fpos_t start;
	fgetpos(stdin, &start);

	while(!feof(stdin) && fgetc(stdin) != '\n')
		dim++;

	fsetpos(stdin, &start);
	
	char str[dim+1];
	fgets(str, dim+1, stdin);
	
	printf("%d\n", mystrlen(str));
}

int mystrlen(char *s){
	int i=0;
	while(s[i] != '\0'){
		++i;
	}
	return i;
}