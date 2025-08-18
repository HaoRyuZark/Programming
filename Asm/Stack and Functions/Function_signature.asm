section .text
global _start

;The stack grows downwards

_start:
    push 21
    call func       ;call pushes the eip(programm counter, aka next instruction) in to the stack and sub 1 to the rsp (stack pointer) 
    mov rax, 1
    int 0x80

func:
    ;function prolog
    push rbp        ;push the value of rbp(base of the stack) on the stack to preseve it
    mov rbp, rsp        ;set val of rbp to rsp. to preserve the top of the stack
    mov rax, [rbp + 8]  ; allocate 2 bytes create stack frame!!!!

    ;also push other registers in to the stack if needed 

    ;function body
    add rax, rax        ; add rax

    ;function epilog
    mov rsp, rbp        ; set the stack pointer back to the preserved value
    pop rbp             ; drop the val of rbp stored in the prolog

    ret         ;pops the val of eip (next instrucion, aka return addr) back to eip and decrements the rsp

