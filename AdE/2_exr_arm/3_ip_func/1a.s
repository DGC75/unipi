    .data
s:  .string "%d\n"
    .text
	
    .globl IP
    .type IP,%function
IP:	
    @R0=X, R1=Y,R2=n
    @R3=i, R4={temp_diff}, R5={RISULTATO SOMMA DEI PRODOTTI}, R6 R7 ={Xi, Yi}
    PUSH {R4, R5, R6, R7, LR}
    MOV R3, #0
    MOV R5, #0
    loop:
        @while(n-i>0)
        SUBS R4, R2, R3
        BEQ end
        LDR R6, [R0, R3, LSL #2]
        LDR R7, [R1, R3, LSL #2]
        MLA R5, R6, R7, R5
        ADD R3, R3, #1
        B loop
    end:
        MOV R0, R5
        
    POP {R4, R5, R6, R7, PC}
