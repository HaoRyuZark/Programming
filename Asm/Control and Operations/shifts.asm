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

