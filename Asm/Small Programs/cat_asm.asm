global _start
section .text

_start:
    mov rax, 2
    mov rdi, [rsp+16]
    mov rsi, 0
    mov rdx, 0
    syscall
    mov rsi, rax
    mov rdi, 1
    mov rax, 40
    mov rdx, 0
    mov r10, 256
    syscall
    jmp $

