
    .text
	
    .globl call_me
    .type call_me,%function
call_me:
    ADD R0, R0, #10
    MOV PC, LR
