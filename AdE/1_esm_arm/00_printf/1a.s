        .data
fmt:    .string "Il valore del registro e': %d\n"

        .text
        .global main
main:   mov r2, #234
        
        @preparazione parametri attuali
        ldr r0, =fmt
        mov r1, r2

        @chiamata funzione
        bl printf

        @ritorno funzione
        mov r7, #1          @implementa una syscall (exit 0)
        svc 0
    