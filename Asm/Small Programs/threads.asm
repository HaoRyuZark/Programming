section .data
    counter dq 0          ; Shared counter initialized to 0
    mutex dd 0            ; Mutex for synchronization
    stack1 rb 4096        ; Stack for thread 1
    stack2 rb 4096        ; Stack for thread 2

section .bss

section .text
    global _start

_start:
    ; Create the first thread
    mov rdi, rsp          ; Parent stack pointer
    sub rdi, stack1       ; Allocate stack space for the new thread
    mov rsi, 0xFFFFFFFF   ; Flags (all cloned)
    lea rdx, [thread1]    ; Thread function
    mov r10, 0            ; No new TLS
    mov r8, 0             ; No child tid
    mov r9, 0             ; No new cgroup
    mov rax, 56           ; clone syscall number
    syscall

    ; Create the second thread
    mov rdi, rsp          ; Parent stack pointer
    sub rdi, stack2       ; Allocate stack space for the new thread
    mov rsi, 0xFFFFFFFF   ; Flags (all cloned)
    lea rdx, [thread2]    ; Thread function
    mov r10, 0            ; No new TLS
    mov r8, 0             ; No child tid
    mov r9, 0             ; No new cgroup
    mov rax, 56           ; clone syscall number
    syscall

    ; Wait for threads to finish
    mov rax, 60           ; exit syscall number
    xor rdi, rdi          ; exit status 0
    syscall

thread1:
    ; Increment the shared counter
    call lock_mutex
    inc qword [counter]
    call unlock_mutex
    ; Exit the thread
    mov rax, 60           ; exit syscall number
    xor rdi, rdi          ; exit status 0
    syscall

thread2:
    ; Increment the shared counter
    call lock_mutex
    inc qword [counter]
    call unlock_mutex
    ; Exit the thread
    mov rax, 60           ; exit syscall number
    xor rdi, rdi          ; exit status 0
    syscall

lock_mutex:
    ; Lock the mutex
    mov eax, 0x81         ; FUTEX_WAIT
    mov edi, mutex
    xor esi, esi
    mov edx, 1
    syscall
    ret

unlock_mutex:
    ; Unlock the mutex
    mov eax, 0x82         ; FUTEX_WAKE
    mov edi, mutex
    mov esi, 1
    syscall
    ret

