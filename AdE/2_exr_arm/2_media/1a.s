    .data
voti:     .word 1,2,3,4,5,6,7,8,9,-1
s:  .string "%d\n"
e:  .string "Lista vuota\n"
    .text
    .globl main
main:
    PUSH {LR}
    @R0 =VOTI, R1=SUM,R2=n(in elaboraione), R3=val corrente arr, R4=tmp check
    LDR R0, =voti
    MOV R1, #0
    MOV R2, #0
    
loop:
    LDR R3, [R0, R2, LSL #2]
    ADDS R4, R3, #1  
    BEQ there
    ADD R1, R1, R3
    ADD R2, R2, #1
    B loop


there:
    @(if R2==0, then exit)
    MULS R0, R2, R2
    BEQ exit
    MOV R0, #0
div:@ESEGUI R1/R2 -> R0
    SUBS R1, R1, R2
    BMI end
    ADD R0, R0, #1
    B div

end:
    MOV R1, R0
    LDR R0, =s
    PUSH {R1}
    bl printf
    POP {R0}
    POP {PC}


exit:
    LDR R0, =e
    bl printf
    MOV R7, #1
    MOV R0, #1
    SVC 0  
  