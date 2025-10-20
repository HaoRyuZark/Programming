# Assembly 

This is the lowest you can get before encountering binary. 
Assembly is heavy dependent on the architecture of the processor because it maps directly to 
the actual instructions of the processor. We will use `x86` asssembly because it is the most widely 
used for personal computers. `ARM` is also  very common but this machine uses `x86` :)

This documents only will cover the most common intructions, system calls and topics to 
programm in assembly. For the full topic, there is the Intel Reference Manual.

--- 

## Registers 

Modern computers used 64-bit systems. The registers in Intel and AMD uses are 
allways exted versions of the previous systems thus, you can still access the 
portion of the register with less bits with its old name. 

### General-Purpose Registers (GPRs)


| 64-bit  | Function / Typical Use                                       | Lower-bit Variants (32 / 16 / 8-bit) |
| :------ | :----------------------------------------------------------- | :----------------------------------- |
| **RAX** | Accumulator for arithmetic operations, return value register | EAX / AX / AH-AL                     |
| **RBX** | Base register, often used to hold data pointers              | EBX / BX / BH-BL                     |
| **RCX** | Counter register, loop counters, shift/rotate count          | ECX / CX / CH-CL                     |
| **RDX** | Data register, used in multiplication/division               | EDX / DX / DH-DL                     |
| **RSI** | Source index for string and memory operations                | ESI / SI / SIL                       |
| **RDI** | Destination index for string and memory operations           | EDI / DI / DIL                       |
| **RBP** | Base pointer for stack frames                                | EBP / BP / BPL                       |
| **RSP** | Stack pointer (top of the stack)                             | ESP / SP / SPL                       |
| **R8**  | General-purpose register                                     | R8D / R8W / R8B                      |
| **R9**  | General-purpose register                                     | R9D / R9W / R9B                      |
| **R10** | General-purpose register                                     | R10D / R10W / R10B                   |
| **R11** | General-purpose register                                     | R11D / R11W / R11B                   |
| **R12** | General-purpose register                                     | R12D / R12W / R12B                   |
| **R13** | General-purpose register                                     | R13D / R13W / R13B                   |
| **R14** | General-purpose register                                     | R14D / R14W / R14B                   |
| **R15** | General-purpose register                                     | R15D / R15W / R15B                   |


### Instruction Pointer and Flags


| Register   | Function / Typical Use                                | Notes                                                                  |
| :--------- | :---------------------------------------------------- | :--------------------------------------------------------------------- |
| **RIP**    | Instruction pointer (address of next instruction)     | Automatically updated by CPU; can be used with RIP-relative addressing |
| **RFLAGS** | Status flags register (condition codes, control bits) | Contains CF, ZF, SF, OF, PF, DF, IF, etc.                              |


### Segment Registers (mostly legacy)


| Register | Function                                     | Notes                                                     |
| :------- | :------------------------------------------- | :-------------------------------------------------------- |
| **CS**   | Code segment                                 | Defines current code segment; mostly fixed in 64-bit mode |
| **DS**   | Data segment                                 | Legacy; usually ignored in x64                            |
| **ES**   | Extra segment                                | Legacy; usually ignored in x64                            |
| **FS**   | Extra segment (used in thread-local storage) | Still used for TLS and OS-specific data                   |
| **GS**   | Extra segment (used in thread-local storage) | Commonly used for kernel or TLS structures                |
| **SS**   | Stack segment                                | Legacy; ignored in x64 (flat memory model)                |

---

### Control Registers (System-level)


| Register | Function / Use                                                   | Notes                                        |
| :------- | :--------------------------------------------------------------- | :------------------------------------------- |
| **CR0**  | System control flags (enables/disables paging, protection, etc.) | Contains PE, MP, EM, TS, PG, etc.            |
| **CR2**  | Page-fault linear address                                        | Used in page fault handling                  |
| **CR3**  | Page table base address                                          | Holds address of page directory base         |
| **CR4**  | CPU feature control bits                                         | Enables PAE, SSE, SMAP, etc.                 |
| **CR8**  | Task priority register                                           | Controls interrupt priority level (x64 only) |


### Debug Registers


| Register    | Function               | Notes                                  |
| :---------- | :--------------------- | :------------------------------------- |
| **DR0–DR3** | Hardware breakpoints   | Store linear addresses for breakpoints |
| **DR6**     | Debug status register  | Reports cause of debug exception       |
| **DR7**     | Debug control register | Enables/disables hardware breakpoints  |


### SIMD / Floating-Point Registers


| Register        | Function / Type                           | Lower-bit Variants                         |
| :-------------- | :---------------------------------------- | :----------------------------------------- |
| **XMM0–XMM15**  | 128-bit SSE registers                     | None (but used as low 128 bits of YMM/ZMM) |
| **YMM0–YMM15**  | 256-bit AVX registers                     | Low 128 bits are XMM registers             |
| **ZMM0–ZMM31**  | 512-bit AVX-512 registers                 | Low 256 bits are YMM registers             |
| **ST(0)–ST(7)** | x87 80-bit floating-point stack registers | Used by legacy FPU instructions            |
| **MM0–MM7**     | 64-bit MMX registers                      | Alias lower part of ST registers           |


--- 

## Memory Addressing 

In assembly we have three types of addressing 

- **Immediate:** `ADD RAX, 5` this handles direct values.

- **Direct:** `ADD RAX, [5]` here the write the value stored at the address 5.

- **Indirect:** `ADD RAX, [RBX]` similar to the last one but by dereferecing another register.

--- 

## Numbers 

In assembly, numbers in other base different from 10 can be used by adding a prefix to the number's start
Using them is similar like in `C`

```c

int b = 0b10010; // Binary

int o = 0222; // Octal 

int hex = 0xFFFF; // Hexadecimal
```

### Floating-Point Numbers 

Floating point numbers are special and they have specialized registers.

```asm
section .data
  x dd 3.14
  y dd 5.4

section .text
global _start

_start:
  movss xmm0, [x]
  movss xmm1, [y]
  addss xmm0, xmm1
  
  movss xmm0, 0.5
  movss xmm1, 0.3
  ucomiss xmm0, xmm1 ;jb, ja, je  (comparations)
  ja greater
  jmp end


greater:
  mov ecx, 1
end:
  mov ebx, 1
  int 80h


```

--- 

## Sections

### Common Sections in x86-64 Assembly


| Section                        | Purpose / Description                          | Typical Contents                                                   | Notes                                                |
| :----------------------------- | :--------------------------------------------- | :----------------------------------------------------------------- |:--------------------------------------------------- |
| **.text**                      | Contains executable machine code               | Functions, instructions                                            | Code segment; usually marked read-only + executable  |
| **.data**                      | Stores initialized global and static variables | Global/static vars with known values (e.g. `int x = 5;`)           | Allocated in memory at load time                     |
| **.bss**                       | Holds uninitialized global/static variables    | Global/static vars initialized to zero or uninitialized (`int x;`) | Occupies no space in the executable (just size info) |
| **.rodata**                    | Read-only data section                         | Constant strings, literal values (`const char *msg = "hi";`)       | Sometimes merged with `.text` depending on linker    |
| **.data.rel.ro**               | Relocatable read-only data                     | C++ vtables, static const with dynamic addresses                   | Read-only after relocation phase                     |
| **.init**                      | Initialization code section                    | Startup routines (e.g. constructors in C++)                        | Executed before `main()`                             |
| **.fini**                      | Finalization code section                      | Termination routines (e.g. destructors)                            | Executed after `main()` or on program exit           |
| **.comment**                   | Metadata from compiler or assembler            | Version strings, assembler info                                    | Not loaded into memory at runtime                    |
| **.debug***                    | Debug information (optional)                   | Symbol tables, line info                                           | Present only in debugging builds                     |
| **.stack** / **stack segment** | Runtime stack area                             | Function call frames, local vars                                   | Managed at runtime by OS and CPU                     |
| **.heap** / **heap area**      | Dynamic memory area                            | Memory allocated via `malloc`, `new`                               | Managed at runtime by OS memory allocator            |


Normaly, the only sections you are going to need are `.text`, `.data` and `.bss`.

### Memory Layout Overview (Typical Linux x86-64 ELF)

```
+---------------------+  High addresses
| Stack (grows down)  |
+---------------------+
|       ...           |
| Heap (grows up)     |
+---------------------+
| .bss                |
| .data               |
| .rodata             |
| .text               |
+---------------------+  Low addresses
```

--- 

## Labels 

Labels are sections of ource inside out text section. They work as "functions" and help us reduce repeated code.

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

Control flow in assembly determines **which instruction executes next**.
It allows programs to make decisions, repeat actions, and call or return from functions.
In x86-64, control flow is primarily managed through **jumps**, **calls**, **returns**, and **conditional branching**.

### Unconditional Jumps

Unconditional jumps **transfer execution** to a new address or label directly, without testing any condition.

| Instruction | Description                      | Example        |
| :---------- | :------------------------------- | :------------- |
| `jmp label` | Jump to `label`                  | `jmp end_loop` |
| `jmp rax`   | Jump to address in register      | `jmp rbx`      |
| `jmp [mem]` | Jump to address stored in memory | `jmp [ptr]`    |

Example:

```asm
start:
    mov rax, 5
    jmp done
done:
    ret
```


### Conditional Jumps

Conditional jumps depend on **status flags** in the **RFLAGS register**, such as:

* **ZF (Zero Flag)** – Set if result is zero
* **SF (Sign Flag)** – Set if result is negative
* **CF (Carry Flag)** – Set if unsigned overflow occurs
* **OF (Overflow Flag)** – Set if signed overflow occurs

They are usually preceded by a **comparison** (`cmp`, `test`) instruction.

| Instruction   | Condition (if true, jump) | Meaning                   |
| :------------ | :------------------------ | :------------------------ |
| `je` / `jz`   | ZF = 1                    | Equal / Zero              |
| `jne` / `jnz` | ZF = 0                    | Not equal                 |
| `jg` / `jnle` | ZF=0 and SF=OF            | Greater (signed)          |
| `jge` / `jnl` | SF=OF                     | Greater or equal (signed) |
| `jl` / `jnge` | SF≠OF                     | Less (signed)             |
| `jle` / `jng` | ZF=1 or SF≠OF             | Less or equal (signed)    |
| `ja` / `jnbe` | CF=0 and ZF=0             | Above (unsigned)          |
| `jb` / `jnae` | CF=1                      | Below (unsigned)          |


Example:

```asm
cmp rax, rbx
je  equal_label
jl  less_label
jmp done
```


### Looping Instructions

Loops use **conditional jumps** to repeat sections of code.

| Instruction   | Description                                      | Notes                 |
| :------------ | :----------------------------------------------- | :-------------------- |
| `loop label`  | Decrement `rcx`; jump if `rcx` ≠ 0               | Uses `rcx` as counter |
| `jecxz label` | Jump if `ecx` = 0                                | Checks before looping |
| `jmp label`   | Commonly used with `cmp` + `j*` for custom loops | Flexible control      |


Example:

```asm
mov rcx, 5
loop_start:
    dec rcx
    jnz loop_start   ; Repeat until rcx = 0
```


### Function Calls and Returns

Functions change control flow to a subroutine and then return back.

| Instruction  | Description                          | Notes                         |
| :----------- | :----------------------------------- | :---------------------------- |
| `call label` | Push return address; jump to `label` | Used for functions            |
| `ret`        | Pop return address; jump back        | Used to return from functions |


Example:

```asm
call print_message
; ... later ...
print_message:
    mov rdi, msg
    call puts
    ret
```


### Indirect Control Flow

Control flow can also depend on register or memory contents — often used for **function pointers** or **jump tables**.

Example:

```asm
jmp [rax]      ; Jump to address stored in rax
call rbx       ; Call function at address in rbx
```

--- 

## Function Calls 

Calling functions involves manipulating the stack related registers to create stack frames, doing operations and finally 
returning to the state before the function was called.

Recap of the importatn registers:

- **RSP:** keeps track of the top of the stack. 

- **RBP:** keeps track of the base of the stack.

- **ISP** points to address of the next instruction to be executed.

Important keywords:

- **CALL:** pushes the current address in the instrucion counter register to the stack.

- **RET:** return to the address at the top of the stack to the instruction rounter register. This should be address 
which was pushed when using `call`.

Note that the stack grows downwards, this means that each time we push something the actual address value gets smaller.

### Function Prolog And Epilog

```asm 

; prolog
push rbp        ; storing the last address of the base of the stack
mov rbp, rsp    ; setting the top of the stack as the base of the stack
sub rsp, 16     ; allocating space for the local variables in the stack  

; body 

;Epilog
add rsp, 16     ; dropping the local variables
mov rsp, rbp    ; setting the stack pointer to its old value
pop rbp         ; setting the base stack register to its old value

ret             
```

How that arguments are passed depends on the **calling convention**, but normaly they are pushed into the stack before 
the function is called.

--- 

## SIMD 

This refers to using one register for multiple operations. We can also treat its content as a vector of numbers. 
This is helpfull for numerical operations.

```asm 
.data
  my_ints1 dd 0, 1, 2, 3, 4
  my_ints2 dd 5, 5, 5, 5, 5

.code

Test proc
  movdqu xmm0, xmmword ptr[my_ints1] 
  movdqu xmm1, xmmword ptr[my_ints2]

  padd xmm0, xmm1 ;add vectors 
  ret             ;to know the exact number of ops for different data types look at AVX512
Test endp
end
```

--- 

## System Calls 

--- 


