ORG 0x7C00  ;starting address of segment of memory ;ORG tells the assembler to read relative to the address
BITS 16     ;number of bits for the OS

jmp short main ;jmp to the main
nop

;Headers for the disk
bdb_oem:                    db 'MSWIN4.1'
bdb_bytes_per_sector:       dw 512
bdb_sectors_per_cluster:    db 1
bdb_reserved_sectors:       dw 1
bdb_fat_count:              db 2
bdb_dir_entries_count:      dw 0E0h
bdb_total_sector:           dw 2880
bdb_media_descriptor_type:  db 0F0h
bdb_sectors_per_fat:        dw 9
bdb_sectors_per_track:      dw 18
bdb_heads:                  dw 2
bdb_hidden_sectors:         dd 0
bdb_large_sector_count:     dd 0

ebr_drive_number:           db 0
                            db 0
ebr_signature:              db 29h
ebr_volume_id:              db 12h,34h,56h,78h
ebr_volume_label:           db 'JAZZ OS    '
ebr_system_id:              db 'FAT12   '


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

    ;setup for reading from disk
    ;mov [ebr_drive_number], dl 
    ;mov ax, 1   ;syscall setup
    ;mov cl, 1
    ;mov bx, 0x7E00 ;pointer to buffer in disk
    ;call disk_read

    ;Print boot message
    mov si, os_boot_msg  ; si points to starting addr of the boot msg
    call print          ; this functions does not modify the state of the registers after execution

    ;4 segments
    ;reserved segment: 1 sector
    ;FAT: 9 * 2 = 18 sector
    ;Root directory: 
    ;Data

    ;get LBA of root dir
    mov ax, [bdb_sectors_per_fat]
    mov bl, [bdb_fat_count]
    xor bh, bh
    mul bx      ;ax * bx stores result in ax
    add ax, [bdb_reserved_sectors] ; LBA of the root directory
    push ax ;preserve data

    mov ax [bdb_dir_entries_count]
    shl ax, 5 ; ax *= 32
    xor dx, dx
    div word [bdb_bytes_per_sector] ;(32*num of entries) / bytes per sector

    test dx, dx
    jz root_dir_after
    inc ax
    

    hlt


;Labels

root_dir_after:
    mov cl, al
    pop ax
    mov dl, [ebr_drive_number]
    mov bx, buffer
    call disk_read

    xor bx, bx
    mov di, buffer

search_kernel:
    mov si, file_kernel_bin
    mov cx, 11
    push di     ;preserve buffer
    repe cmpsb  ;repear comparasion of bytes si with cx
    pop di
    je found_kernel

    add di, 32
    inc bx
    cmp bx, [bdb_dir_entries_count] ;if we reached the end of the dirs
    jl search_kernel

    jmp kernel_not_found


kernel_not_found:
    mov si, msg_kernel_not_found
    call print

    hlt
    jmp halt


found_kernel:
    mov ax, [di + 26] ; address plus cluster
    mov [kernel_cluster], ax

    mov ax, [bdb_reserved_sectors]
    mov bx, buffer
    mov cl, [bdb_sectors_per_fat]
    mov dl, [ebr_drive_number]

    call disk_read

    ;setting up memory for loading the kernel
    mov bx, kernel_load_segment
    mov es, bx
    mov bx, kernel_load_offset

load_kernel_loop:
    mov ax, [kernel_cluster]
    add ax, 31
    mov cl, 1
    mov dl, [ebr_drive_number]

    call disk_read

    add bx, [bdb_bytes_per_sector]

    mov ax, [kernel_cluster]
    mov cx, 3
    mul cx
    mov cx, 2
    div cx

    mov si, buffer
    add si, ax
    mov ax, [ds:si]

    or dx, dx
    jz even

odd:
    shr ax, 4
    jmp next_cluster_after

even:
    and ax, 0x0FFF

next_cluster_after:
    cmp ax, 0x0FF8
    jae read_finish

    mov [kernel_cluster], ax
    jmp load_kernel_loop

read_finnish:
    mov dl, [ebr_drive_number]
    mov ax, kernel_load_segment
    mov ds, ax
    mov es, ax

    jmp kernel_load_segment:kernel_load_offset

    hlt

halt:
    jmp halt


;input: LBA index in ax
;output: cx[bits 0-5]: secotor number
;        cx[bist 6-15]: cylinder
;        dh: head
lba_to_chs:
    push ax
    push dx

    xor dx,dx
    div word [bdb_sector_per_track] ;sector = (LBA % sectors per track) + 1 | divs val in rax or derivatives by the (dividend) in a size
    ;al, ax, eax or rax store the result  (depending on the size)
    ;ah, dx, edx or rdx store the reainder (depending on the size)
    
    inc dx    ;sector
    mov cx, dx

    xor dx, dx
    div word [bdb_heads]

    mov dh, dl ; head
    mov ch, al
    shl ah, 6   ;shift left 6 bits
    or cl, ah   ;cylinder

    ;head: (LBA / sectors per track) % number of heads [will be stored in dx]
    ;cylinder: (LBA / sectors per track) / number of heads [will be stored in ax]
    
    pop ax
    mov dl, al
    pop ax

    ret

disk_read:
    push ax
    push bx
    push cx
    push dx
    push di

    call lba_to_chs

    mov ah, 02h
    mov di, 3 ; counter

retry:
    stc ;set carry
    int 13h         ;reset disk interrupt
    jnc done_read   ;if carry == 0 then no error and proced to done_read

    call disk_reset

    dec di      ;di--
    test di, di
    jnz retry   ;jump if there was an error

fail_disk_read:
    mov si, read_failure
    call print
    hlt
    jmp halt

disk_reset:
    pusha ;push all general p register
    mov ah, 0 ;syscall setup
    stc
    int 13h  ;reset syscall
    jc fail_disk_read
    popa
    ret

done_read:
    pop di  ;restore state of the programm before the call
    pop dx
    pop cx
    pop bx
    pop ax

    ret


print:
    push si  ;preserve state of the register
    push ax  ;by pushing the data in the stack
    push bx

print_loop:
    lodsb          ;load byte of the location pointed by SI and place the char in AL
    or al, al      ; check if the byte is 0 set the 0Flag
    jz done_print   ;if 0Flag == 0 jmp to done_print
    
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


os_boot_msg: db 'Loading...', 0x0D, 0x0A, 0 ;message plus \n and a \0
read_failure db 'Failed to read disk!', 0x0D, 0x0A, 0 ; error message 
file_kernel_bin db 'KERNEL  BIN'
msg_kernel_not_found db 'KERNEL.BIN not found!'
kernel_cluster dw 0

kernel_load_segment equ 0x2000
kernel_load_offset equ 0

TIMES 510-($-$$) db 0 ;($ current instruction - && start of current section ; the expr. calculates how many more bytes needs to be added 
dw 0AA55h             ;to reach a total of 510. Used for set the boot sector

buffer: