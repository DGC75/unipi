.data
etich: .word 70.000

.text
.globl main

main:   
        MOV R0, #99
        MOV R1, #120
        MOV R2, #250

        ADD R0, R0, #99
        ADD R1, R1, #120
        ADD R2, R2, #655366553665536

        LDR R0, =etich


        MOV PC, LR
