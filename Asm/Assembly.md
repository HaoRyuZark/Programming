# Assembly 

This is the lowest you can get before encountering binary. 
Assembly is heavy dependent on the architecture of the processor because it maps directly to 
the actual instructions of the processor. We will use `x86`asssembly because it is the most widely 
used for personal computers. `ARM` is also  very common but this machine uses `x86` :)

This documents only will cover the most common intructions, system calls and topics to 
programm in assembly. For the full topic, there is the Intel Reference Manual.

--- 

## Registers 

Modern computers used 64-bit systems. The registers in Intel and AMD uses are 
allways exted versions of the previous systems thus, you can still access the 
portion of the register with less bits with its old name. 

--- 

## Sections 

--- 

## Numbers 


--- 

## Comparations 

```asm
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
```
--- 

## Strings 

```asm
section .data
        list DB 1,2,4,5     ; list of items
        string1 DB "ABA",0  ; string with null terminator
        char DB 'A'         ;
        string2 DB "CDB",0  ;

section .text
global _start

_start:
      MOV bl, [string1]
      MOV eax, 1,
      XOR ebi, ebi
      SYSCALL
```

--- 

## Structs And Unions 

```asm
section .data

Point struct
  dd x ?
  dd y ?
Point ends

myPoint Point{0 , 0}

MyUnion union
  small db ?
  medium dw ?
  large dd ?
  huge dq ?
MyUnion ends

pp MyUnion{0fffffffh}

section .code

SomeFunc proc
    mov [rcx].Point.x, 100
    mov pp.medium, 100
    ret
SomeFunc endp
end

 
```

--- 

## Moving Data 

--- 

## Logic Operations 

```asm 

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
```

--- 

## Shifts 

```asm
section .data
    msg db 'Result: ', 0
    result db 0

section .bss
    num resb 1

section .text
    global _start

_start:
    ; Initialize a value in the AL register
    mov al, 0b00001111 ; binary: 00001111

    ; Perform SHL (Shift Left Logical) operation
    shl al, 1           ; AL = 00011110 (0x1E)
    mov [num], al

    ; Print result of SHL
    call print_result

    ; Reset the value in AL register
    mov al, 0b00001111

    ; Perform SHR (Shift Right Logical) operation
    shr al, 1           ; AL = 00000111 (0x07)
    mov [num], al

    ; Print result of SHR
    call print_result

    ; Reset the value in AL register
    mov al, 0b00001111

    ; Perform SAL (Shift Arithmetic Left, same as SHL)
    sal al, 1           ; AL = 00011110 (0x1E)
    mov [num], al

    ; Print result of SAL
    call print_result

    ; Reset the value in AL register
    mov al, 0b10001111 ; binary: 10001111

    ; Perform SAR (Shift Arithmetic Right)
    sar al, 1           ; AL = 11000111 (0xC7)
    mov [num], al

    ; Print result of SAR
    call print_result

    ; Reset the value in AL register
    mov al, 0b10001111 ; binary: 10001111

    ; Perform ROL (Rotate Left)
    rol al, 1           ; AL = 00011111 (0x1F)
    mov [num], al

    ; Print result of ROL
    call print_result

    ; Reset the value in AL register
    mov al, 0b10001111 ; binary: 10001111

    ; Perform ROR (Rotate Right)
    ror al, 1           ; AL = 11000111 (0xE7)
    mov [num], al

    ; Print result of ROR
    call print_result

    ; Exit program
    mov eax, 60         ; syscall: exit
    xor edi, edi        ; status: 0
    syscall

print_result:
    ; Print message
    mov eax, 1          ; syscall: write
    mov edi, 1          ; file descriptor: stdout
    lea rsi, [msg]
    mov edx, 8          ; message length
    syscall

    ; Print result
    mov eax, 1          ; syscall: write
    mov edi, 1          ; file descriptor: stdout
    lea rsi, [num]
    mov edx, 1          ; result length
    syscall

    ; Print newline
    mov eax, 1          ; syscall: write
    mov edi, 1          ; file descriptor: stdout
    lea rsi, [newline]
    mov edx, 1          ; newline length
    syscall

    ret

section .data
    newline db 0x0A

```

--- 

## Loops 

```asm 
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
```

---

## Math 

```asm 
section .data
    num1 dd 10       ; Define a 32-bit integer with value 10
    num2 dd 3        ; Define a 32-bit integer with value 3
    result dd 0      ; Variable to store result
    remainder dd 0   ; Variable to store remainder

section .bss
    random dd        ; unitialized var

section .text
    global _start

_start:
    ; Load values into registers
    mov eax, [num1]  ; Move value of num1 into eax
    mov ebx, [num2]  ; Move value of num2 into ebx

    ; Addition: eax = eax + ebx
    add eax, ebx     ; Add ebx to eax, result is stored in eax
    mov [result], eax ; Store the result of addition in result

    ; Subtraction: eax = eax - ebx
    mov eax, [num1]  ; Move value of num1 into eax
    sub eax, ebx     ; Subtract ebx from eax, result is stored in eax
    mov [result], eax ; Store the result of subtraction in result

    ; Multiplication: edx:eax = eax * ebx
    mov eax, [num1]  ; Move value of num1 into eax
    mul ebx          ; Multiply eax by ebx (unsigned multiplication), result in edx:eax
    ; Note: result is 64-bit stored in edx:eax, edx has high 32 bits, eax has low 32 bits
    mov [result], eax ; Store the low 32 bits of the result in result
    ; For signed multiplication, use 'imul' instead of 'mul'

    ; Division: eax = edx:eax / ebx, remainder in edx
    mov eax, [num1]  ; Move value of num1 into eax
    xor edx, edx     ; Clear edx (high 32 bits of dividend must be zero for unsigned division)
    div ebx          ; Divide edx:eax by ebx (unsigned division), quotient in eax, remainder in edx
    mov [result], eax ; Store the quotient in result
    mov [remainder], edx ; Store the remainder in remainder

    ; For signed division, use 'idiv' instead of 'div'

    ; Exit the program
    mov eax, 1       ; sys_exit system call number
    xor ebx, ebx     ; Exit code 0
    int 0x80         ; Call kernel

; Explanation of Registers and Operations:
; eax: Accumulator register, used for arithmetic operations
; ebx: Base register, often used to hold base addresses or variables
; edx: Data register, used in multiplication and division
; add: Adds the source operand to the destination operand and stores the result in the destination operand
; sub: Subtracts the source operand from the destination operand and stores the result in the destination operand
; mul: Multiplies the unsigned value in eax by the source operand, result in edx:eax
; imul: Multiplies the signed value in eax by the source operand, result in edx:eax
; div: Divides the unsigned value in edx:eax by the source operand, quotient in eax, remainder in edx
; idiv: Divides the signed value in edx:eax by the source operand, quotient in eax, remainder in edx
; xor: Performs bitwise exclusive OR, used here to clear the edx register


```

--- 

## Control Flow 

--- 

## Loops 

--- 

## Function Calls 

--- 

## System Calls 

--- 


