        .data
fmt:    .string "%d, %d, %d, %d, %d\n"
rgs:    .string "R%d: %d\n"

        .text
        .global main
main:   

        ldr r0, =rgs
        mov r1, #4
        mov r4, #66
        mov r2, r4

        bl printf

        ldr r0, =rgs
        mov r1, #5
        mov r5, #67
        mov r2, r5

        push {r4, r5}
        bl printf


        @preparazione parametri attuali
        ldr r0, =fmt
        mov r1, #1
        mov r2, #10
        mov r3, #17

        mov r4, #666
        mov r5, #420
        push {r4,r5}
        mov r4, #21
        mov r5, #21



        @chiamata funzione
        bl printf
        pop {r4, r5}

        ldr r0, =rgs
        mov r1, #4
        mov r2, r4

        bl printf

        ldr r0, =rgs
        mov r1, #5
        mov r2, r5

        bl printf


        @ritorno funzione
        mov r7, #1          @implementa una syscall (exit 0)
        svc 0
        