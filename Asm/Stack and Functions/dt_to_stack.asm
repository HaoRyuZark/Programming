addTwo:
    push ebp                ;   |  ebp      |   <-esp   push ebp to stack
    mov ebp, esp            ;   |  ret addr | +4 (distance)   set ebp to point to the sa,e as the esp
    mov eax, [ebp+8]        ;   |  1        | +8              access data directly in the stack
    mov ebx, [ebp+12]       ;   |  4        | +12             same as above
    add eax, ebx            ;   add data                  
    pop ebp                 ;   pop ebp so that esp decreases by one an points to the return address
    ret                     ;  return the val to the return address

main: 
  push 4  ; 4 to stack
  push 1  ; 1 to stack
  call addTwo
  mov ebx, eax
  mov eax, 1
