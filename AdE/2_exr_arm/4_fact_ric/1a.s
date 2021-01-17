    .data
s:  .string "%d\n"
    .text

    .globl main

main:
    PUSH {LR}
    MOV R0, #5
    BL fact
    MOV R1, R0
    LDR R0, =s
    bl printf
    POP {PC}

fact:
    PUSH {LR}
    SUBS R1, R0, #1
    BEQ ret
    PUSH {R0}
    SUB R0, R0, #1
    BL fact
    POP {R1}
    MUL R0, R0, R1
    POP {PC}

    ret:
        POP {PC}
