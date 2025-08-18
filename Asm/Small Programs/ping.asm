global _start


section .data

address: 
  dw 2                 ; AF_INET (Address Family: IPv4)
  dw 0                 ; Port number (placeholder, to be set later)
  db 8, 8, 8           ; Partial IP address
  db 8                 ; Remaining part of IP address
  dd 0                 ; Reserved/Unused
  dd 0                 ; Reserved/Unused

packet:
  db 8                 ; Packet data (8)
  db 0                 ; Packet data (0)

checksum:
  dw 9                 ; Checksum value (9)
  dw 0                 ; Unused/Reserved
  dw 1                 ; Unused/Reserved

buffer:
times 1024 db 0ffh     ; Buffer of 1024 bytes, initialized to 0xff

good: db 'good'        ; String "good"

section .text

_start:
  ; Create a socket
  mov rax, 41          ; syscall number for socket
  mov rdi, 2           ; AF_INET (IPv4)
  mov rsi, 3           ; SOCK_STREAM (TCP)
  mov rdx, 1           ; IPPROTO_IP (IP protocol)
  syscall              ; Invoke the syscall

  ; Save the socket file descriptor
  mov r12, rax         ; Store the socket file descriptor in r12

  ; Negate the first word of checksum
  not word [checksum]  ; Bitwise NOT operation on the first word of checksum

  ; Connect to the address
  mov rax, 44          ; syscall number for connect
  mov rdi, r12         ; File descriptor of the socket
  mov rsi, packet      ; Pointer to the packet data
  mov rdx, 18          ; Size of the packet
  mov r10, 0           ; Reserved (set to 0)
  mov r8, address      ; Pointer to the address
  mov r9, 16           ; Size of the address
  syscall              ; Invoke the syscall

  ; Receive data into the buffer
  mov rax, 45          ; syscall number for recv
  mov rdi, r12         ; File descriptor of the socket
  mov rsi, buffer      ; Pointer to the buffer
  mov rdx, 1024        ; Size of the buffer (1024 bytes)
  mov r10, 0           ; Flags (set to 0)
  mov r8, 0            ; Reserved (set to 0)
  mov r9, 0            ; Reserved (set to 0)
  syscall              ; Invoke the syscall

  ; Check if the data at buffer+20 is 0
  cmp word [buffer+20], 0 ; Compare the word at buffer+20 with 0
  jne failure          ; If not equal, jump to failure

  ; If check succeeds, print "good" to standard output
  mov rax, 1           ; syscall number for write
  mov rdi, 1           ; File descriptor (stdout)
  mov rsi, good        ; Pointer to the string "good"
  mov rdx, 4           ; Length of the string
  syscall              ; Invoke the syscall

failure:
  jmp $                ; Infinite loop to prevent exiting

