section .text
global _start

_start:
    mov eax, 0b1010
    mov ebx, 0b1100
    and eax, ebx    ;and or, not xor etc
    mov eax, 0b1010
    mov ebx, 0b1100
    not eax           ;sal, sar, shr, shl "shifts"
    int 80
    int 80h
