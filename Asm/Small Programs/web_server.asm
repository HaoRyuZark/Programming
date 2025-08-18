; This assembly code sets up a simple TCP server using the x86-64 architecture for the Linux operating system.
; The server listens on a specified port and serves the content of a file ("index.html") to the client.

format ELF64                  ; Specify the format of the output file as 64-bit ELF.
public _start

; Constants for system call numbers and other parameters
socket = 41      ; System call number for socket creation
bind = 49        ; System call number for binding a socket to an address
listen = 50      ; System call number for listening on a socket
accept = 43      ; System call number for accepting a connection on a socket
read = 0         ; System call number for reading from a file descriptor
write = 1        ; System call number for writing to a file descriptor
open = 2         ; System call number for opening a file
exit = 60        ; System call number for exiting a process
close = 3        ; System call number for closing a file descriptor
af_inet = 2      ; Address family for IPv4
sock_stream = 1  ; Type for TCP (stream) sockets
o_rdonly = 0     ; Flag for opening a file in read-only mode

section '.text' executable  ; Defines the text section (code) as executable
_start:
    ; Create a socket
    mov rdi, af_inet        ; Set first argument (domain) to AF_INET (IPv4)
    mov rsi, sock_stream    ; Set second argument (type) to SOCK_STREAM (TCP)
    mov rdx, 0              ; Set third argument (protocol) to 0 (default)
    mov rax, socket         ; Set syscall number for socket
    syscall                 ; Make syscall to create socket

    mov r12, rax            ; Save the socket file descriptor in r12

    ; Bind the socket to an address
    mov rdi, r12            ; Set first argument (socket fd) to the value in r12
    mov rsi, address        ; Set second argument (pointer to sockaddr) to address
    mov rdx, 16             ; Set third argument (length of sockaddr) to 16 bytes
    mov rax, bind           ; Set syscall number for bind
    syscall                 ; Make syscall to bind socket

    ; Listen for connections
    mov rdi, r12            ; Set first argument (socket fd) to the value in r12
    mov rsi, 10             ; Set second argument (backlog) to 10
    mov rax, listen         ; Set syscall number for listen
    syscall                 ; Make syscall to listen on socket

accept_loop:
    ; Accept a connection
    mov rdi, r12            ; Set first argument (socket fd) to the value in r12
    mov rsi, 0              ; Set second argument (pointer to sockaddr) to 0 (null)
    mov rdx, 0              ; Set third argument (length of sockaddr) to 0
    mov rax, accept         ; Set syscall number for accept
    syscall                 ; Make syscall to accept connection

    mov r13, rax            ; Save the client socket file descriptor in r13

    ; Read request from client
    mov rdi, r13            ; Set first argument (client socket fd) to the value in r13
    mov rsi, buffer         ; Set second argument (buffer) to buffer
    mov rdx, 256            ; Set third argument (buffer size) to 256 bytes
    mov rax, read           ; Set syscall number for read
    syscall                 ; Make syscall to read from client socket

    ; Open the file
    mov rdi, path           ; Set first argument (filename) to path
    mov rsi, o_rdonly       ; Set second argument (flags) to O_RDONLY (read-only)
    mov rax, open           ; Set syscall number for open
    syscall                 ; Make syscall to open file

    mov r14, rax            ; Save the file descriptor for "index.html" in r14

    ; Read file contents
    mov rdi, rax            ; Set first argument (file fd) to the value in r14
    mov rsi, buffer2        ; Set second argument (buffer) to buffer2
    mov rdx, 256            ; Set third argument (buffer size) to 256 bytes
    mov rax, read           ; Set syscall number for read
    syscall                 ; Make syscall to read from file

    ; Write response to client
    mov rdi, r13            ; Set first argument (client socket fd) to the value in r13
    mov rsi, buffer2        ; Set second argument (buffer) to buffer2
    mov rdx, 256            ; Set third argument (buffer size) to 256 bytes
    mov rax, write          ; Set syscall number for write
    syscall                 ; Make syscall to write to client socket

    ; Close client socket
    mov rdi, r13            ; Set first argument (client socket fd) to the value in r13
    mov rax, close          ; Set syscall number for close
    syscall                 ; Make syscall to close client socket

    ; Close file descriptor
    mov rdi, r14            ; Set first argument (file fd) to the value in r14
    mov rax, close          ; Set syscall number for close
    syscall                 ; Make syscall to close file descriptor

    ; Jump back to accept_loop to handle next connection
    jmp accept_loop

    ; Exit program (Unused)
    mov rdi, 0              ; Set first argument (exit code) to 0
    mov rax, exit           ; Set syscall number for exit
    syscall                 ; Make syscall to exit program

section '.data' writeable   ; Defines the data section as writable
address:
    dw af_inet              ; Address family (IPv4)
    dw 0x901f               ; Port number (8080 in hex, network byte order)
    dd 0                    ; IP address (0.0.0.0 for any address)
    dq 0                    ; Padding
buffer:
    db 256 dup 0            ; Buffer for reading client request (256 bytes)
buffer2:
    db 256 dup 0            ; Buffer for reading file contents (256 bytes)
path:
    db 'index.html', 0      ; Null-terminated string for filename

