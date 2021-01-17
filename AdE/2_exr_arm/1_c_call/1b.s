    .data
s: .string "%d\n"

    .text  
    .global main

main:
    MOV R0, #0
    bl call_me

    MOV R1, R0
    LDR R0, =s

    bl printf

    MOV R7, #1
    SVC 0 
       