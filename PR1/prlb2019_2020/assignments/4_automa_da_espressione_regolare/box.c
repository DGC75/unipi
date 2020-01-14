#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_STATES 11

int move				(int (*)(char c), char c);
_Bool isFinal			(int state);
void go_to_trap_state	(void);

/*TRANSITION TABLE FUNCTIONS DECLARATION*/

int state_0 	(char c);
int state_1   	(char c);
int state_2 	(char c);
int state_3 	(char c);
int state_4		(char c);
int state_5		(char c);
int state_6		(char c);
int state_7		(char c);
int state_8		(char c);
int state_9		(char c);
int state_10	(char c);


int main(void){

	/*TRANSITION TABLE FOR THE DFA*/
	int (*trans_table[NUM_STATES])(char c) = {
		state_0, state_1, state_2,  state_3,
		state_4, state_5, state_6,  state_7,
		state_8, state_9, state_10};

	/*CODE FOR SIMULATING THE DFA*/
	int S = 0;
	char c;

	c = getchar();	
	while(c != '\n'){
		S = move(trans_table[S],c);
		c = getchar();
	}
	if(isFinal(S))
		puts("stringa appartenente al linguaggio");
	else
		puts("stringa non appartenente al linguaggio");
}


_Bool isFinal(int state){
	if(state >= 7 && state <= 10)
		return true;
	else
		return false;
}


int move(int (*state)(char c), char c){
	return state(c);
}

void go_to_trap_state(void){
	puts("stringa non appartenente al linguaggio");
	exit(0);	
}

int state_0(char c){
	/*IF AZ GO TO 0*/
	if (isupper(c)){
		return 0;
	}
	else if (c == '0'){
		return 1;
	}

}

int state_1(char c){
	if (isdigit(c)){
		if (c == '1'){
			return 3;
		}
		return 2;
	}
	go_to_trap_state();
}

int state_2(char c){
	/*IF AZ GO TO 0*/
	if (isdigit(c)){
		return 4;
	}
	go_to_trap_state();
}

int state_3(char c){
	if (isdigit(c)){
		if (c == '1'){
			return 6;
		}
		return 5;
		}	
	go_to_trap_state();
}

int state_4(char c){
	if (isdigit(c)){
		return 7;
	}
	go_to_trap_state();	
}

int state_5(char c){
	if (isdigit(c)){
		return 8;
	}
	go_to_trap_state();	
}

int state_6(char c){
	if (isdigit(c)){
		if (c == '1'){
			return 10;
		}
		return 9;
		}	
	go_to_trap_state();
}

int state_7(char c){
	go_to_trap_state();
}

int state_8(char c){
	if (isdigit(c)){
		return 7;
	}
	go_to_trap_state();	
}

int state_9(char c){
	if (isdigit(c)){
		return 8;
	}
	go_to_trap_state();	
}

int state_10(char c){
	if (isdigit(c)){
		if (c == '1'){
			return 10;
		}
		return 9;
	}
	go_to_trap_state();	
}
