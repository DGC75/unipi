    .text
    .globl cambia
    .type cambia,%function
cambia:
        //R0 = s (string)
        //R1 = l
        //R2 = ls
        //R3 = sum
        //R4 = i
        //R5 = cc
        //R6 = s[i]
        PUSH {R4, R5, R6, LR}
        PUSH {R0, R1, LR}
        BL strlen
        MOV R2, R0
        POP {R0, R1, LR}
        MOV R3, #0
        MOV R4, #0

loop:   
        @check condition
        CMP R4, R2 //i - ls
        BGE end
        @call cifra, and save to R5
        PUSH {R0,R1,R2,R3,LR}
        LDRB R0, [R0, R4]
        MOV R6, R0 //R6 = s[i]
        BL cifra
        MOV R5, R0
        POP {R0,R1,R2,R3,LR}
        @check if
        CMP R5, R6
        STRNEB R5, [R0, R4]
        ADDNE R3, R3, #1

        @i++
        ADD R4, R4, #1
        B loop
end:
        MOV R0, R3
        POP {R4, R5, R6, PC}
