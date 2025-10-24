ORG 0x7C00  ;starting address of segment of memory ;ORG tells the assembler to read relative to the address
BITS 16     ;number of bits for the OS

;Disk addresing
;CHS: Cylinder, Head, Sector (tuple)
;LBA: Logical Block Addresing (integer)

;CHS to LBA = (C * TH * TS) + (H * TS) + (S - 1)
;C sector cylinder number
;TH  total header on disk
;TS total sections on disk
;H sector head
;S sector number

;LBA to CHS
;t = LBA/sector per track
;s = LBA % sectors per track + 1
;h = t % number of heads
;c = t/number of heads  

;Main Entry Point
main:
    ;Setup for execution
    mov ax, 0  ; set ax to 0 for a safe start
    mov ds, ax ; ds start addr of the data segment
    mov es, ax ; es start point of the extra segment
    mov ss, ax ; ss start addr of the stack
    mov sp, 0x7C00 ; stack pointer to the initial the address of the programm

    ;Print boot message
    mov si, os_boot_msg  ; si points to starting addr of the boot msg
    call print          ; this functions does not modify the state of the registers after execution

    hlt

halt: 
    jmp halt

print:
    push si  ;preserve state of the register
    push ax  ;by pushing the data in the stack
    push bx

print_loop:
    lodsb          ;load byte of the location pointed by SI and place the char in AL
    or al, al      ; check if the byte is 0 set the 0Flag
    Jz done_print   ;if 0Flag == 0 jmp to done_print
    
    ;Case 0Flag != 0
    mov ah, 0x0E   ;mov tval to h. The val represents the code for the bios to print a char to the screen
    mov bh, 0      ;set the page number. Current monitor
    int 0x10       ;video interrupt. Tells the bios to check the al and prints the char

    jmp print_loop

done_print:
    pop bx  ;restore registers
    pop ax
    pop si
    ret     ;mov the stack pointer to the addr of the next instruction

os_boot_msg: db 'Our OS has booted', 0x0D, 0x0A, 0 ;message plus \n and a \0

TIMES 510-($-$$) db 0 ;($ current instruction - && start of current section ; the expr. calculates how many more bytes needs to be added 
dw 0AA55h             ;to reach a total of 510. Used for set the boot sector
