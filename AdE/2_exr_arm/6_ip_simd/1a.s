        .data
s:      .string "%d\n"

        .text
        .global main
main:
    ldr r0, =0x01010101
    ldr r1, =0x02020202
    vmov d0, r0, r0
    vmov d1, r1, r1
    vmul.i8  d2, d1, d0
    vpadd.i8 d2, d2


    MOV PC, LR
