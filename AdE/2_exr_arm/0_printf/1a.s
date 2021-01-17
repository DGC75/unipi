    .data
s:  .string "il numero vale %d\n"

    .text
	
    .globl main
main:
    PUSH {LR}
    LDR R0, =s
    MOV R1, #4

    bl printf
    MOV R1, R0
    LDR R0, =s

    bl printf
    POP {PC}
    
    @MOV R7, #1
    @SVC 0
    
