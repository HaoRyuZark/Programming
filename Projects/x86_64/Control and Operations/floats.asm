section .data
  x dd 3.14
  y dd 5.4

section .text
global _start

_start:
  movss xmm0, [x]
  movss xmm1, [y]
  addss xmm0, xmm1
  
  movss xmm0, 0.5
  movss xmm1, 0.3
  ucomiss xmm0, xmm1 ;jb, ja, je  (comparations)
  ja greater
  jmp end


greater:
  mov ecx, 1
end:
  mov ebx, 1
  int 80h


