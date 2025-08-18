global _start

section .data

buffer: 
  times 256 db 0

section .text

_start:
  mov rax, 79
  mov rdi, buffer
  mov rsi, 256
  syscall

  mov rax, 1
  mov rdi, 1
  mov rsi, buffer
  mov rdx, 256
  syscall

jmp $



