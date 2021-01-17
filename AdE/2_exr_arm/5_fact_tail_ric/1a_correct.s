    .data
s:  .string "%d\n"

    .text
    .globl main
main:
            @R0=n
            @R1=acc
            @default call:(n, 1)
            PUSH {LR}
            MOV R0, #5
            MOV R1, #1
            BL fact_t
print:
            MOV R1, R0
            LDR R0, =s
            PUSH {R1}
            bl printf
            POP {R0}
ret_main: 
            POP {PC}
fact_t:     
            CMP R0, #1
            BEQ ret_fact
            MUL R1, R0, R1
            SUB R0, R0, #1
            B   fact_t


ret_fact:
            MOV R0, R1
            MOV PC, LR
