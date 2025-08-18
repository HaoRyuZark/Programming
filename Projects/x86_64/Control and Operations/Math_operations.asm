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


