section .data
        list db 1,2,3,4
section .text
global _start

_start:
      mov eax, 0
      mov cl,  0

loop:
      mov bl, byte ptr [list + eax] ;or just [list + eax]
      add cl, bl  ;add the current value to the cl register
      inc eax     ;eax++
      cmp eax, 4  ; cmp if eax == 4
      je end      ;terminate
      jmp loop    ;loop

end:
      mov eax, 1
      mov ebx, 1
      int 80h
