# Systems Programming

Systems programming involves writing software that provides services to the computer hardware. This includes operating systems, device drivers, and other low-level software that interacts directly with the hardware. To understand systems programming, one must be familiar with the architecture of the computer, including how memory is managed, how processes are scheduled, and how input/output operations are performed. This document covers low level concepts which are essential for systems programming.

---

## Size of Variables

In contrast to high-level languages, low-level languages like C allow you to control the size of variables explicitly. The size of a variable can affect performance and memory usage. Here are some common variable sizes in C:

- `char`: 1 byte
- `short`: 2 bytes
- `int`: 4 bytes
- `long`: 4 or 8 bytes (depending on the architecture)
- `float`: 4 bytes
- `double`: 8 bytes

By understanding the size of different data types, you can make informed decisions about memory allocation and optimize your programs for better performance.

---

## Binary System

The binary system, or base-2 numeral system, is a number system that uses only two symbols: 0 and 1. 
This system is fundamental to all modern computers and digital devices because their 
circuits operate on two states: on (1) or off (0). Unlike the decimal system (base-10), which uses 
powers of 10, the binary system uses powers of 2. For example, the decimal number 9 is represented in binary as 1001, which
is calculated as 

```
(1 times2 3
 )+(0
times2 
2
 )+(0
times2 
1
 )+(1
times2 
0
 )=8+0+0+1=9.
```

---

## Binary Operations

Binary operations are performed similarly to decimal operations but with only two 
digits.

### Addition ➕

```
0+0=0

0+1=1

1+0=1

1+1=10 (which is 0 with a carry-over of 1)

1+1+1=11 (which is 1 with a carry-over of 1)

```

Example: 1011_2+101_2

```
  1011
+  101
------
  10000
```

### Subtraction ➖

Subtraction is done using borrowing.

Example: 101_2−11_2

```
  101
-  011
------
   010
```

### Multiplication ✖️

Binary multiplication is a series of additions and shifts.

Example: 101_2 times 11_2

```
   101
 x  11
------
   101  (101 x 1)
+ 1010  (101 x 1, shifted left by one place)
-------
  1111
```

### Division ➗
Binary division is similar to long division in the decimal system, using repeated subtraction.

Example: 1101_2 div 10_2

```
      110.1
   _______
10 | 1101.0
   - 10
   ------
      10
     - 10
     ------
       01
      - 00
      ------
        10
       - 10
       ------
         0
```

---

## Two's Complement

Two's complement is a method used to represent signed (positive and negative) integers 
in binary. It simplifies arithmetic operations, particularly subtraction, by allowing 
it to be performed as addition. To find the two's complement of a number:

- Invert the bits (change all 0s to 1s and 1s to 0s). This is also known as finding the one's complement.

- Add 1 to the result.

For example, to represent −5 using 8 bits:

```
The positive binary representation of 5 is 00000101.

Invert the bits: 11111010.

Add 1: 11111010+1=11111011.

Thus, 11111011 represents −5 in two's complement. This system is crucial for a computer's arithmetic logic unit (ALU) as it avoids the need for a separate subtraction circuit.
```

---

## Conversions: Decimal, Binary, and Hexadecimal

### Decimal to Binary

To convert a decimal number to binary, you repeatedly divide the decimal number by 2 and record the remainders. The binary number is the sequence of remainders, read from bottom to top.

Example: Convert 13_10 to binary.

```
13
div2=6 remainder 1

6
div2=3 remainder 0

3
div2=1 remainder 1

1
div2=0 remainder 1
```

Reading the remainders from the bottom up, we get 1101_2.

### Binary to Decimal

To convert a binary number to decimal, multiply each digit by its corresponding power of 2 and sum the results.

Example: Convert 1101_2 to decimal.

```
(1×2 
3
 )+(1×2 
2
 )+(0×2 
1
 )+(1×2 
0
 )
=(1×8)+(1×4)+(0×2)+(1×1)=8+4+0+1=13 
10
```
 
### Binary to Hexadecimal (Hex)

Hexadecimal (base-16) is a number system that uses 16 symbols (0−9 and A−F). It's a compact way to represent binary numbers. To convert binary to hex, group the binary digits into sets of four, starting from the right. Then, convert each group into its hex equivalent.

Example: Convert 11011010_2 to hex.

```
Group the digits: 1101 and 1010.

1101_2=13_10, which is D in hex.

1010_2=10_10, which is A in hex.

Result: DA_16.
```

### Hexadecimal to Binary

To convert hex to binary, simply convert each hex digit into its 4-bit binary equivalent.

Example: Convert 2A_16 to binary.

```
2_16=0010_2

A_16=1010_2
```

Combine the results: 00101010_2.

---

## Floating-Point Numbers

Floating-point numbers are used to represent real numbers (numbers with fractional parts) in binary, similar to scientific notation. They are represented by a sign bit, an exponent, and a mantissa (or significand). The IEEE 754 standard is the most widely used format for floating-point arithmetic.

- Sign bit: 0 for positive, 1 for negative.

- Exponent: Determines the magnitude of the number. It's stored in a biased format.

- Mantissa: Represents the precision digits of the number.

This format allows a wide range of values, from very small fractions to very large numbers, to be represented accurately within a fixed number of bits.

---

## Binary Multiplication

Binary multiplication is essentially a series of shift-and-add operations. For each '1' in the multiplier, the multiplicand is added to a running total, shifted to the left by the appropriate number of places.

---

## Binary Division

Binary division, often implemented using repeated subtraction, works much like long division in the decimal system. The divisor is repeatedly subtracted from the dividend, and a '1' is placed in the quotient for each successful subtraction. If the subtraction is not possible, a '0' is placed in the quotient, and the next digit of the dividend is brought down.

---

## Numbers in C 

In the `C` programming language numbers in other base different from 10 can be used by adding a prefix to the number's start

```c

int b = 0b10010; // Binary

int o = 0222; // Octal 

int hex = 0xFFFF; // Hexadecimal
```

--- 

## Memory Management

Memory management is a critical aspect of systems programming. It involves allocating and deallocating memory for variables and data structures. In C, memory management is done using functions like `malloc`, `calloc`, `realloc`, and `free`.

Example of memory allocation in C:

```C

#include <stdio.h>
#include <stdlib.h>
int main() {
    
    int* arr;
    int n = 5;

    // Allocate memory for an array of 5 integers
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize and print the array
    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;
        printf("%d ", arr[i]);
    }
    
    // Free the allocated memory
    free(arr);
    
    return 0;
}

```

---

## Pointers

Pointers are a fundamental concept in low-level programming. They allow you to directly manipulate memory addresses, which is crucial for performance and resource management. A pointer is a variable that stores the address of another variable.

Example of using pointers in C:

```c
#include <stdio.h>

int main() {

int var = 42;
    
    int* ptr = &var;

    printf("Value of var: %d\n", var);
    printf("Address of var: %p\n", (void *)&var);
    printf("Value of ptr: %p\n", (void *)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);
    
    int** dptr = &ptr;

    printf("Dereferencing double pointer %d", **ptr);
    return 0;
}
```


### Cursed Pointers

Here some examples of "weird" pointers in C:

```c

// Function pointer example
void (*func_ptr)(int); // pointer to a function that takes an int and returns void

//Really cursed pointers 

int (*x())[10]; //  x is a function that returns a pointer to an array of 10 integers 
int (*((*x)[]))() // x is a pointer to an array of pointers to functions that return int
char *(*(*x[8][8])())[10]; // x is a 2D array of pointers to functions that return pointers to arrays of 10 chars
```

### Strings and Char Buffers in C

In C, strings are represented as arrays of characters terminated by a null character ('\0'). Unlike higher-level languages, C does not have a native string type—just character arrays.

```c
char str1[] = "Hello";       // Size is automatically 6 (5 + null terminator)
char str2[10] = "Hi";        // Manually specified size, with extra space
char *str3 = "World";        // Pointer to a string literal (read-only)
```

#### Char Buffers

A char buffer is just a character array that can hold a string, often used for input/output or manipulation:

```c
char buffer[100];  // Buffer that can store up to 99 characters + '\0'
```

You can use functions like strcpy, strcat, strlen, and strcmp from <string.h> to work with these buffers.

#### Common Pitfalls

Always ensure there’s enough space for the null terminator `('\0')`.

Be careful with buffer overflows—C doesn’t do bounds checking.

Writing to string literals (like char *s = "text";) is undefined behavior.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char name[20];
    strcpy(name, "Alice");
    strcat(name, " Smith");
    printf("Full name: %s\n", name);
    return 0;
}
```

---

## Bit Manipulation

Bit manipulation is a powerful technique in systems programming that allows you to perform operations at the bit level. This can be useful for optimizing performance, reducing memory usage, and implementing low-level protocols.

Example of bit manipulation in C:

```C
#include <stdio.h>
int main() {
    unsigned int x = 5; // 0000 0101 in binary
    unsigned int y = 3; // 0000 0011 in binary

    // Bitwise AND
    unsigned int and_result = x & y; // 0000 0001
    printf("AND result: %u\n", and_result);

    // Bitwise OR
    unsigned int or_result = x | y; // 0000 0111
    printf("OR result: %u\n", or_result);

    // Bitwise XOR
    unsigned int xor_result = x ^ y; // 0000 0110
    printf("XOR result: %u\n", xor_result);

    // Bitwise NOT
    unsigned int not_result = ~x; // 1111 1010 (assuming 8-bit representation)
    printf("NOT result: %u\n", not_result);

    return 0;
}
```

### Bit fields 

Is a series of bits where individual bits have meaning. They can be used to safe space, increase performance, etc. 
A common use is networking where we want to send compact packages.

```c
#include <stdio.h>
#include <stdint.h>

// File open flags (up to 8 bits)
#define F_READ     0x01  // 0000 0001
#define F_WRITE    0x02  // 0000 0010
#define F_APPEND   0x04  // 0000 0100
#define F_CREATE   0x08  // 0000 1000
#define F_TRUNC    0x10  // 0001 0000
#define F_BINARY   0x20  // 0010 0000

void open_file(const char *filename, uint8_t flags) {
   
   printf("Opening file: %s\n", filename);

    if (flags & F_READ)
        printf(" - Mode: READ\n");

    if (flags & F_WRITE)
        printf(" - Mode: WRITE\n");

    if (flags & F_APPEND)
        printf(" - Option: APPEND\n");

    if (flags & F_CREATE)
        printf(" - Option: CREATE if not exists\n");

    if (flags & F_TRUNC)
        printf(" - Option: TRUNCATE existing file\n");

    if (flags & F_BINARY)
        printf(" - Option: BINARY mode\n");
}


int main() {

    uint8_t flags = F_READ | F_WRITE | F_CREATE;

    open_file("data.txt", flags);

    return 0;
}
```

### Bit Masks 

It is a binary pattern used to modify anoher binary pattern using bitwise operations. 

---

## Structs 

A struct is a contiguous block of memory which contaings enough memory for all members plus padding for addressing the word size. Mostly 
64 bits or 8 bytes.

## Unions

Similar to struct it also a way of grouping data but it only allocates enough to hold the biggest member. It can only be 
in one of its variants at the time.

## Casting String-numbers to Numbers 

Multiple programming languages have defaults for converting string to numbers. The way this functionality works is by 
using the ASCII enconding which for the digits starts at 48. Therefore to convert a character number to a number the computer 
subtracts 48 from the binary code of the character. For multiple numbers with multiple digits a system for the positions has to be accounted.

---

## The Stack

Is a memory region that stores local variables, function parameters, and return addresses. It operates in a last-in, first-out (LIFO) manner. The data is stored contiguously, and the stack grows downwards in memory. Each function call creates a new stack frame that contains the function's local variables and parameters.

---

## Function Inlining and Outlining 

When compilers or the programmer himself generates/writes code, there is the choice between 
repeating the same code over and over again or writing function. If we focus on the compiler perspective, 
we will realize that jumping in memory multiple times can be expensive in terms of performance. Due to this fact the compiler 
tries as much as possible to do function **inlining**, but this can also lead to big binary sizes. 

Contrary to inlining, **outlining** is based on jumping to the address of the of the instructions.

---

## The Heap

The heap is a memory region used for dynamic memory allocation. Unlike the stack, memory in the heap is managed manually by the programmer using functions like `malloc`, `calloc`, `realloc`, and `free`. The heap allows for more flexible memory usage, but it also requires careful management to avoid memory leaks and fragmentation. The heap is considered slower than the stack for memory allocation and deallocation because it involves more complex bookkeeping. This slowness is caused by the fragmentation of the memory.

---

## Cache

Cache is a small, fast memory located close to the CPU that stores frequently accessed data. It helps speed up data retrieval by reducing the time it takes to access data from the main memory (RAM).

When the requested data is found in the cache, it is called a cache hit; if not, it is a cache miss, and the data must be fetched from the slower main memory. There is
a caching hierarchy, typically consisting of multiple levels (L1, L2, L3), with L1 being the fastest and smallest, and L3 being larger but slower. If data is not used frequently, it may be evicted from the cache to make room for new data.

---

## System Calls

System calls are the interface between user applications and the operating system kernel. They allow user programs to request services from the kernel, such as file operations, process management, and network communication. System calls provide a controlled way for applications to interact with hardware and system resources.

---

## Fetch Decode Execute Cycle

The fetch-decode-execute cycle is the fundamental process by which a CPU executes instructions. It consists of three main stages:

1. **Fetch**: The CPU retrieves an instruction from memory, typically from the instruction cache or main memory, using the program counter (PC) to determine the address of the next instruction.
2. **Decode**: The fetched instruction is decoded to determine what operation it specifies and which operands are involved. This step involves interpreting the binary representation of the instruction.
3. **Execute**: The CPU performs the operation specified by the instruction, which may involve arithmetic or logical operations, memory access, or control flow changes. The results of the execution are then stored back in memory or in registers.
4. **Repeat**: The cycle repeats for the next instruction, with the program counter being updated to point to the next instruction in the sequence.

---

## Pipelining

Pipelining is a technique used in modern CPUs to improve instruction throughput by overlapping the execution of multiple instructions. Instead of executing one instruction at a time, the CPU divides the instruction execution process into several stages, allowing different instructions to be processed simultaneously at different stages.

This done in the following way:

```txt
Fetch -> Decode -> Execute
        Fetch -> Decode -> Execute
                 Fetch -> Decode -> Execute
```

This cylce is regulated by the computer clock using flip-flops in chain to delay the signal of the clock. This 
is done in that way to mitigate the effects of the intermidiate states of the delay generated by the transitions between zero and one.

The chain flip-flops also creates a binary counter which can be used to control the phases of execution by incrementing the counter and using the ouput for a binary 
decoder.

Actually, this proccess is very complex, and CPU's can actually predict branches, execute instructions out of order and some other stuff to minimize iddle time. 

---

## When does The OS Run

The OS is a process itself, and it runs whenever the CPU is not executing user code. It is loaded into memory when the computer boots and then can be invoked in several ways:

- **System Calls**: When a user program requests a service from the OS, such as file access or process management, it triggers a system call that switches the CPU to kernel mode to execute the OS code.
- **Interrupts**: Hardware devices can generate interrupts to signal the CPU that they require attention. When an interrupt occurs, the CPU stops executing the current user program, stores the context and switches to the OS to handle the interrupt. This is build into the CPU architecture.
- **Exceptions**: These are unexpected events that occur during program execution, such as division by zero or invalid memory access. When an exception occurs, the CPU switches to the OS to handle the error.
- **Context Switching**: The OS can preempt a running user program to give CPU time to another process. This is done through context switching, where the OS saves the state of the current process and loads the state of the next process to be executed.

--- 

## Memory Layout of a Process

The memory layout of a process typically consists of several segments:

- **Text Segment**: Contains the executable code of the program.
- **Data Segment**: Contains global and static variables.
- **BSS Segment**: Contains uninitialized global and static variables.
- **Heap Segment**: Used for dynamic memory allocation.
- **Stack Segment**: Contains local variables and function call information.

---

## Virtual Memory

Virtual memory is a memory management technique that allows a computer to use more memory than is physically available by using disk space as an extension of RAM. It also provides the illusion of a large, contiguous memory space to applications, while the operating system manages the mapping between virtual addresses and physical addresses.

It is done by dividing the memory into fixed-size pages and mapping them to physical memory frames. When a program accesses a page that is not currently in physical memory, a page fault occurs, and the OS retrieves the required page from disk and updates the mapping.

Via hardware support, such as the Memory Management Unit (MMU), virtual memory allows for efficient memory usage, isolation between processes, and protection against unauthorized access. This unit is also responsible for managing the page table, which keeps track of the mapping between virtual addresses and physical addresses.

---

## ABI

The Application Binary Interface (ABI) defines how different components of a binary program interact at the machine level. It specifies details such as calling conventions, data types, and system calls, ensuring that compiled code can run on a specific platform without requiring recompilation.

---

## Processes

A **proces** is an instance of a program.


### PCB 

The **process control block** is an abstraction the operating sytem uses to identify processes. 
An over simplification would be 

```rust 
pub struct PCB {
    pid: u16,
    state: Process_state,
    program_counter: u16,
    instruction_register: u8,
}

```

Processes from the perspective of the operating system require this strucure to be handled by the context switching. This is also considered the 
CPU state of the process.


## IPC 

This stands for the term **inter process communication**. The two main approaches are **shared memory** and 
**message passing**. The first one is very simple because is just depends on telling the operating system that preocesses 
agree to use the memory region in an specific format. The preferred way is to use an specific region of memory of the OS address space 
to create a queue or queues in which data from the processes can be communicatees can be communicatedd, this is the second approach.

The previously mentioned queues or more informal mailboxes for processes are called **ports**.

--- 

## Interrupts

Interrupts are implemented at hardware level to store the state of the CPU correctly. One variant is to use 
two register sets. One for the user mode and one for the kernel mode. 

Another way is to make the stack register of the OS always visible to the CPU via a hardwired memory location or register. So 
during the context switching the all critical registers can be stored correctly.

---

## User Mode and Kernel Mode

The mode bit is an special register which allows the cpu to execute privileged instructions. This mode is called **kernel mode**, and 
is used by the operating system. The **user mode** is used for other programms which need the operating system or drivers to run. 

The value of the register is modified by an interrupt. 

The CPU contains a timer to automatically return control to the OS in the case a process does not voluntarelly return control.

---

## CPU Scheduling

CPU scheduling is the process of deciding which of the processes in the ready queue will be allocated to the CPU. The primary motivation behind CPU scheduling is to maximize CPU utilization and provide a responsive system for users. A well-designed scheduling algorithm aims to ensure that the CPU is never idle as long as there are processes ready to run, while also providing a fair and efficient allocation of CPU time among competing processes. Scheduling is a fundamental concept in multiprogramming operating systems, where multiple processes can reside in memory at the same time. The scheduler is a key component of the operating system that makes these allocation decisions.

### Cooperative and Preemptive Scheduling

There are two main approaches to CPU scheduling: cooperative and preemptive.

- Cooperative scheduling relies on a process to voluntarily give up the CPU. A running process will continue to use the CPU until it either terminates or explicitly yields the CPU. This type of scheduling is simple to implement but can lead to a system becoming unresponsive if a single process enters an infinite loop or a long computation without yielding. In such a scenario, no other processes would get a chance to run.

- Preemptive scheduling is a more robust approach where the operating system can interrupt a running process and force it to give up the CPU. This is typically done after a certain time interval, known as a time slice, has elapsed, or when a higher-priority process becomes ready. Preemptive scheduling ensures that no single process can monopolize the CPU, leading to a more responsive and fair system. It is the dominant approach in modern operating systems.


### Scheduling Strategies

Several algorithms and strategies are used to implement CPU scheduling, each with its own advantages and disadvantages. The choice of strategy often depends on the goals of the system (e.g., maximizing throughput, minimizing response time, or ensuring fairness).

- **First-Come, First-Served (FCFS)**: This is the simplest scheduling algorithm, where processes are executed in the order they arrive in the ready queue. FCFS is a non-preemptive algorithm that is easy to implement but can result in a phenomenon called the convoy effect, where a long-running process at the front of the queue can cause all subsequent processes to wait, leading to poor average waiting times.

- **Shortest-Job-Next (SJN)**: This algorithm selects the process with the smallest estimated execution time to run next. SJN can be either preemptive (Shortest Remaining Time First) or non-preemptive. It is an optimal algorithm for minimizing the average waiting time, but it has a major drawback: it requires knowing the future execution time of a process, which is impossible in practice. In practice, this is often estimated based on past behavior.

- **Priority Scheduling:** This strategy assigns a priority level to each process, and the CPU is allocated to the process with the highest priority. Priority can be based on factors such as process type, memory requirements, or the user who initiated it. A key problem with priority scheduling is starvation, where a low-priority process may never get to run if there is a continuous stream of high-priority processes. This can be mitigated through a technique called aging, where the priority of a process increases over time.

- **Round-Robin (RR) Scheduling:** This is a preemptive algorithm designed for time-sharing systems. Each process is given a small unit of CPU time, called a time quantum or time slice. When the time quantum expires, the process is preempted and added to the end of the ready queue. RR provides a fair share of the CPU to each process and is generally effective for interactive systems where response time is a key concern. The performance of RR is highly dependent on the size of the time quantum. A small quantum can lead to frequent context switches, which can increase overhead, while a large quantum can make it behave like FCFS.

---

## Signals 

**Signals** are a way of inter-process communication. They are used to communicate a process an specific behaviour like terminating, halting, 
resuming etc. They are provided the OS to trigger interrupts directly.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int interrupt_count = 0;

// Signal handler function
void handle_sigint(int sig) {
    interrupt_count++;
    printf("\nCaught signal %d (SIGINT). Interrupt count: %d\n", sig, interrupt_count);

    if (interrupt_count >= 3) {
        printf("Too many interrupts. Exiting now.\n");
        exit(0);
    }
}

int main() {
    // Register signal handler
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to send SIGINT. Program will exit after 3 interrupts.\n");

    // Infinite loop
    while (1) {
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}
```
---

## Concurrency And parallelism

Concurrency and parallelism are two related concepts in computer science that deal with the execution of multiple tasks simultaneously.

- **Concurrency** refers to the ability of a system to handle multiple tasks at the same time, but not necessarily executing them simultaneously. It involves managing multiple tasks that may be in progress at the same time, allowing for better resource utilization and responsiveness. This is done on a single CPU core by interleaving the execution of tasks, giving the illusion that they are running simultaneously.

- **Parallelism** on the other hand, involves executing multiple tasks simultaneously, typically on multiple CPU cores or processors. This can lead to significant performance improvements for compute-intensive tasks. In contrast to concurrency, parallelism requires multiple processing units to execute tasks at the same time, effectively dividing the workload among them.

- **Address Space**  is the memory region used by a process.

--- 

## Threads

Threads are inner entities in a process which can be executed concurrently inside a process. They have their own CPU state and are 
handled via syscalls for creation, deletion and execution. When the OS changes from the one process to another it will excute the 
threads which are not sleeping.

From the OS perspective a thread is not very different from a process but for a developer it is 
way to inform the operating system that specific regions of a program can be executed concurrently.

---

## Memory protection

Because checking for memory security each time a processes is executed would be very costly in terms of performance this ascpect is implemented via hardware.

The condition is: **address >= base and address < base + limit**

--- 

## Sleep 

This instruction is used to voluntarelly give the CPU to another process for an specific time.
It uses an sleeping queue to regulate the use of the computer inner timmer via software. 

--- 

## Race Conditions

Race conditions occur when multiple threads or processes access shared resources concurrently, and the final outcome depends on the timing of their execution. This can lead to unpredictable behavior and bugs in the program. It is important to note that spanning multiple threads does not guarantee parallel execution, as the operating system may schedule them on a single core, leading to interleaved execution. But this can still result in race conditions if not properly managed.

--- 

## Atomic Operations

Atomic operations are operations that are completed in a single step relative to other threads. They are indivisible and cannot be interrupted, ensuring that no other thread can see an intermediate state. This is crucial for preventing race conditions and ensuring data consistency in concurrent programming. The mostly consist of simple operations like incrementing a counter or setting a flag, and they are typically implemented using low-level hardware instructions that guarantee atomicity.

--- 

## Mutexes and Condition Variables

Mutexes (mutual exclusions) and condition variables are synchronization primitives used to manage access to shared resources in concurrent programming. Mutexes provide a way to lock a resource so that only one thread can access it at a time, preventing race conditions.

Condition variables allow threads to wait for certain conditions to be met before continuing execution, enabling more complex synchronization patterns.

Both approaches use **atomic operations** to ensure no race conditions occur.

---

## Cores 

Moder processors have multiple cpus which can improve performance both for processes and threads. This is handled by the 
operating system.

---

## Drivers 

A **driver** is a software made to communicate with hardware components. They make the development 
of the OS by regarding the specific software for all peripherals to the fabricants.

--- 

## GCC Compiler Process 

- Preprocessor → Inserts macros, eliminates comments etc. 
- Compiler     → Generates the assembly code fromt the C file. 
- Assembler    → Takes the assembly file and generates an object file which consists of headers and the binary machine structions. It is not executable. 
- Linker       → Takes the object file/s and links them togethter to create an executable.

---

## Header Files 

Header files `.h` are used to declare functions, structs etc. They are used to tell the compiler tool chain 
which functions are declared, but header files require also a concrete executable or object file of a `.c` file to work. 

### Strucure

```c
#ifndef SOME_NAME_H // this guard helps against infinite recursion
#define SOME_NAME_H

...

#endif
```

### Includes 

To include a header file of a local project we use `"header.h"` and to include one that is globally installed on the system 
`<header.h>`.

---

## Memory Mapped IO 

A way code can control hardware is via special region of memory which 
can not normally be accessed because of compiler optimizations unless the keyword `volatile` is used in `C`, for example.

This region of memory has special connections to the direct hardware or microcontroller of the device we want to control. Therefore, 
by writing specific values to it we can send signals which get decoded by the circuit and are translated into the reality as for example 
turning on pixel.

---

## Firmware 

It is embeded into the hardware. Nowadays it is called **UEFI** and before it was called **BIOS**. It loads the 
bootloaders and they also provide some functionality for configurations.

--- 

## Bootloaders 

It is reponsible for launching the OS. It reads an specific sector in the disk to do this. 

---

# Networking

Networking in computer science refers to concept of connection of 
multiple computers.

---

## Ports 

A **port** is a communication endpoint. They are identified by a number and for the operating system, they are a logical construct to identify a process or a 
type of network service. Note that the at the hardware level we also have ports for audio, video, etc., but this are completely different ports.

Ports are regions of memory in the address-space of the operating system. Thus, the OS is reponsible for them.

--- 

## Sockets

Sockets are an abstraction provided by the operating system to enable communication 
between different processes either on the same machine or over a network. They act as 
endpoints in a two-way communication channel. **Socket = Protocol + IP Address + Port Number**. 

Sockets operate primarily at the **Transport** layer of the **OSI** model. They are called from the 
**Application** layer asking to send or receive data. Then the socket wrap it via **TCP/UDP** and send it to 
the **Network** layer.

They are handled by the operating system and commonly provided by **libc**. 

---

## What is a File Descriptor?

A **file descriptor (FD)** is a low-level integer handle used by an operating system to uniquely identify an open file or input/output (I/O) resource. File descriptors are central to how operating systems like Unix, Linux, and macOS manage I/O operations, including files, pipes, and sockets.

### Key Characteristics:

* **Integer Identifier**: File descriptors are represented by non-negative integers (e.g., `0`, `1`, `2`).
* **Resource Handle**: Each FD refers to an open I/O resource, such as a file, socket, or device.
* **Process-specific**: FDs are unique within a process and are maintained by the process’s file descriptor table.

### Standard File Descriptors:

By default, every process starts with three open file descriptors:

| FD | Name     | Description     |
| -- | -------- | --------------- |
| 0  | `stdin`  | Standard input  |
| 1  | `stdout` | Standard output |
| 2  | `stderr` | Standard error  |


### File Descriptors and Sockets:

In networking, **sockets are treated like files**. When you create a socket using `socket()`, the system returns a file descriptor that you can use for reading and writing data:

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// sockfd is now a file descriptor for a socket
```

This file descriptor can be used with functions like `read()`, `write()`, `close()`, or `select()` just like regular files.

### Why File Descriptors Matter:

* They provide a **uniform interface** for I/O operations.
* Used heavily in **multiplexing I/O** (e.g., `select()`, `poll()`, `epoll()`).
* Essential for **resource management**—every open FD consumes system resources.

### Closing File Descriptors:

To free up system resources, file descriptors must be explicitly closed using:

```c
close(sockfd); // Closes the socket and releases the FD
```

Failing to close file descriptors can lead to **resource leaks**, limiting how many files or sockets a program can open simultaneously.

### TLDR

In short, file descriptors are integers which represent a current open file.

---

## OSI Model

It as framework for working with networks. It stands for **Open System Interconnection**. It consist of the following layers:

- **Application:**  It provides network services for the users by providing protocols like Brave.
- **Presentation:** Performs the task of syntax processing. This means to translate layer from application format to network format and viceversa
- **Session:**      It supports the construction direction and construction of connections of devices. 
- **Transport:**    This layer takes care of the transport of data across the network.
- **Network:**      It handles the routin of the data. 
- **Data Link:**    It receives the data and packages it into frames which are going to be send to the respective targets.
- **Physical:**     This layer consist on the electrical part of the network. In general the hardware.

---

## UDP and TCP

When it comes to computer networking, **UDP (User Datagram Protocol)** and **TCP (Transmission Control Protocol)** are two core transport layer protocols used to send data over the Internet. Each has its own characteristics, strengths, and ideal use cases.

### TCP (Transmission Control Protocol)

TCP is a **connection-oriented** protocol, meaning it establishes a reliable connection between sender and receiver before data transfer begins. It ensures that data is delivered **accurately and in the correct order**. For this it uses a **three-way handshake** which constist of: 
**SYN ->**, **<-SYN ACK** and finally **ACK->**.

**Key features of TCP:**
- **Reliable**: Uses acknowledgments (ACKs), retransmissions, and checksums to ensure data arrives intact.
- **Ordered**: Guarantees the sequence of data packets.
- **Error-checked**: Detects errors and corrects them through retransmission.
- **Flow control**: Manages the rate of data transmission to avoid overwhelming the receiver.
- **Connection-based**: Requires a handshake (three-way handshake) before data is exchanged.

**Common use cases:** Web browsing (HTTP/HTTPS), email (SMTP, IMAP, POP3), file transfers (FTP), and other applications requiring reliable communication.

### UDP (User Datagram Protocol)

UDP is a **connectionless** protocol that sends data without establishing a connection first. It prioritizes **speed over reliability**, making it faster but less reliable than TCP.

**Key features of UDP:**
- **Unreliable**: No guarantee of delivery, order, or duplication protection.
- **No handshakes**: Sends data without establishing a connection.
- **Lightweight**: Less overhead compared to TCP.
- **Broadcast and multicast support**: Useful for sending data to multiple recipients at once.

**Common use cases:** Online gaming, video streaming, voice over IP (VoIP), DNS queries, and other time-sensitive applications where speed is more critical than accuracy.

### Summary

| Feature              | TCP                           | UDP                          |
|----------------------|-------------------------------|------------------------------|
| Connection           | Connection-oriented            | Connectionless               |
| Reliability          | Reliable (ACKs, retransmissions) | Unreliable (no ACKs)        |
| Speed                | Slower due to overhead         | Faster, minimal overhead     |
| Use cases            | Web, email, file transfer      | Gaming, streaming, VoIP      |

Choosing between TCP and UDP depends on the needs of the application—**reliability and order** with TCP, or **speed and simplicity** with UDP.

---

## Socket Lifecycle

The **socket lifecycle** represents the stages a network socket goes through during communication between a client and a server. Understanding this lifecycle is crucial for developing reliable networked applications using either TCP or UDP.

Below is a typical **TCP socket lifecycle**, presented as a top-to-bottom flow with arrows:

```
Client Side                        Server Side
------------                      ------------

   [Socket()]                      [Socket () (creation)]
        ↓                                ↓
[Connect Request]                    [bind() (bind to port)]
        ↓                                ↓
   [connect()] ----------------> [listen() (listening for connections)]
        |                                ↓
        |                            [accept()]
        ↓                                ↓
   [Data Transfer] <----------->  [Data Transfer read() or write()]
        ↓                                ↓
   [close()]  <------------------     [close()]
```

### Lifecycle Stages (TCP):

1. **Socket Created**
   Both client and server create a socket using system calls (e.g., `socket()` in C or Python).

2. **Bind (Server only)**
   The server binds its socket to a specific IP address and port using `bind()`.

3. **Listen (Server only)**
   The server starts listening for incoming connections using `listen()`.

4. **Connect (Client)**
   The client initiates a connection to the server using `connect()`.

5. **Accept (Server)**
   The server accepts the connection using `accept()`, creating a new socket for the client.

6. **Data Transfer**
   Both sides can send and receive data using `send()` and `recv()`.

7. **Close Connection**
   Once communication is done, both sides close their sockets using `close()` or `shutdown()`.

---

## Unix Domain Sockets

**Unix Domain Sockets (UDS)** are a method of inter-process communication (IPC) that allows data exchange between processes running on the same host. Unlike network sockets that use IP addresses and port numbers, Unix Domain Sockets use file system pathnames as their addressing mechanism.

### Key Characteristics

- **Local Communication Only**: UDS can only be used for communication between processes on the same machine.
- **Performance**: They offer lower latency and higher throughput compared to TCP/IP sockets due to bypassing the network stack.
- **Security**: Access control is enforced through standard file system permissions.
- **Socket Types**: Supports `SOCK_STREAM` (like TCP), `SOCK_DGRAM` (like UDP), and `SOCK_SEQPACKET`.

### Typical Use Cases

- Communication between a web server (e.g., Nginx) and an application server (e.g., uWSGI or Gunicorn).
- Fast, secure IPC in containerized or tightly controlled environments.
- Replacement for loopback TCP connections where performance and security are critical.

### Example

Here’s how to create a Unix domain socket in Python:

```python
import socket
import os

server_address = '/tmp/uds_socket'

# Make sure the socket does not already exist
try:
    os.unlink(server_address)
except FileNotFoundError:
    pass

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Bind the socket to the address
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

print(f"Listening on {server_address}")
```

---

### Command ip link

In linux the `ip link` command will return three device names

- `lo` for the loop back device
- `Ethernet Plug`
- `Ẁifi card`

## Network Protocols

A protocol is a set of for transmitting data across a network.

- **Adress Resolution Protocol ARP:** Used for the mapping to MAC addresses.
- **Ethernet:** Used for the direct connection in a network.
- **Internet Control Protocol:** It is for testing reachability and other manners across the internet.

## SSH

Secure shell is a protocol used for providing a secure encrypted connection to a remote machine. It uses asymmetric encryption
and commonly port 22 for the connection.

### Layout

```txt
| Packet length -- Padding Amount -- Payload Padding -- Message Authentication |
```

Everything between packet length and message authentication is encrypted.

---

## I/O Devices

To control hardware the CPU does not actually perform the operations directly, but it uses smaller computers 
build into the devices called **mirco-controllers**. The communication can be stablished via 
memory mapped io or by isolated io which uses specific buses and components.
