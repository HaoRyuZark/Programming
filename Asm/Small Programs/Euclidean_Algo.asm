section .data
    x dd 7
    y dd 5

section .text
    global main

main:
    mov rax, [x]       ; load x into rax
    mov rbx, [y]       ; load y into rbx

    call gcd_loop

    hlt

gcd_loop:
    cmp rbx, 0         ; if y (rbx) is 0, we are done
    je done

    xor rdx, rdx       ; clear rdx for division
    div rbx            ; rax = rax / rbx, rdx = remainder

    mov rax, rbx       ; move y to rax
    mov rbx, rdx       ; move remainder to rbx (new y)
    jmp gcd_loop       ; repeat until remainder is zero

done:
    ; GCD is now in RAX
    ret                ; return with gcd in rax
