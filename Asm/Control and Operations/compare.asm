section .data
_global start
            ;jl, jne, jg, je, jz, jnz, jump if lower, not equal, greater, zero, equal, not zero etc...
start:
      mov eax, 3
      mov ebx, 2
      cmp eax, ebx ;makes a substraction and based on that determines if the register a or b is greater or equal 
      jl lesser ; if the result of eax is lower than ebx jump to the lesser routine
      jmp end   ;otherwise we are gonna jmp to the end "jmp" always executes

      int 80h
lesser:
      mov ecx, 1
      int 80h
      
end:
    int 80h
