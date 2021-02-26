    .text
    .globl cifra
    .type  cifra,%function

cifra:
    //RO = char c
    //R1 = int n
    //R2 = 'a' 
    //R3 = 'z'
    //R4 = cc

    //PUSH EVENTUALE DI REGISTRI PRESERVATI
    PUSH {R4, LR}

    LDR R2, =0x61
    LDR R3, =0x7a
    CMP R3, R0  //z - c
    BMI ret
    CMP R0, R2  //c - a
    BMI ret
    ADD R4, R0, R1 //cc = c + n
    MOV R0, R4     //cc becomes r0

    CMP R0, R3     //cc - z
    BLS ret
    SUB R0, R0, R3
    ADD R0, R0, R2
    SUB R0, R0, #1

ret:
    //POP EVENTUALE DI REGISTRI PRESERVATI
    POP {R4, PC}

