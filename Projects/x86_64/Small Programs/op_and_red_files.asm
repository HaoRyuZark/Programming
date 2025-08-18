section .data
  pathname dd "/home/....."

section .bss
  buffer: resb 1024

section .text
global main 

main:
  mov eax,5 ; 5 to syscall "Open file"
  mov ebx, pathname ;pointer to string
  mov ecx, 0 ; exit code
  int 80h   ;syscall

  mov ebx, eax ;store file descriptor
  mov eax, 3   ;val for system call
  mov ecx, buffer
  mov edx, 1024
  int 80h   ;syscall

  mov eax, 1
  mov ebx, 0
  int 80h

