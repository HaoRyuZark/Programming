# Systems Programming

--- 

## Layers of a Computer 

- **Applications**: compilers, editor, guis, etc.
- **Libraries and Critical Programs**: language Libraries and global executables.
- **OS**: kernel for the interaction with the hardware.
- **Hardware**: Physical layer.

--- 

## Tasks of an Operating System

- **Process Management**: Handling the life span of a program as well as allowing multitasking.
- **Memory Management**: Management of the resources of a program.
- **File system**: Definition of how data is going to be stored, retrieved, updated and deleted.
- **Input/Output**: Handling peripherals for the entering or display of data.

--- 

## Size of Data Types

- `char`: 1 byte
- `short`: 2 bytes
- `int`: 4 bytes
- `long`: 4 or 8 bytes (depending on the architecture)
- `float`: 4 bytes
- `double`: 8 bytes

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

### Addition 

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

### Subtraction 

Subtraction is done using borrowing.

Example: 101_2−11_2

```
  101
-  011
------
   010
```

### Multiplication 

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

### Division

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

Floating-point numbers are used to represent real numbers (numbers with fractional parts) in binary, similar to scientific notation. They are represented 
by a sign bit, an exponent, and a mantissa (or significand). The IEEE 754 standard is the most widely used format for floating-point arithmetic.

- Sign bit: 0 for positive, 1 for negative.

- Exponent: Determines the magnitude of the number. It's stored in a biased format.

- Mantissa: Represents the precision digits of the number.

This format allows a wide range of values, from very small fractions to very large numbers, to be represented accurately within a fixed number of bits.

---

## Binary Multiplication as Shifts

Binary multiplication is essentially a series of shift-and-add operations. For each '1' in the multiplier, the multiplicand is added to a running total, shifted to the left by the appropriate number of places.

---

## Binary Division

Binary division, often implemented using repeated subtraction, works much like long division in the decimal system. The divisor is repeatedly subtracted from the dividend, and a '1' is placed in the quotient for each successful subtraction. If the subtraction is not possible, a '0' is placed in the quotient, and the next digit of the dividend is brought down.

---

## The Stack

Is a memory region that stores local variables, function parameters, and return addresses. It operates in a last-in, first-out (LIFO) manner. The data is 
stored contiguously, and the stack grows downwards in memory. Each function call creates a new stack frame that contains the function's local variables and parameters.

---

## Function Inlining and Outlining 

When compilers or the programmer himself generates/writes code, there is the choice between 
repeating the same code over and over again or writing function. If we focus on the compiler perspective, 
we will realize that jumping in memory multiple times can be expensive in terms of performance. Due to this fact the compiler 
tries as much as possible to do function **inlining**, but this can also lead to big binary sizes. 

Contrary to inlining, **outlining** is based on jumping to the address of the of the instructions.

---

## The Heap

The heap is a memory region used for dynamic memory allocation. Unlike the stack, memory in the heap is managed manually by the programmer using functions 
like `malloc`, `calloc`, `realloc`, and `free`. The heap allows for more flexible memory usage, but it also requires careful management to avoid memory leaks 
and fragmentation. The heap is considered slower than the stack for memory allocation and deallocation because it involves more complex bookkeeping. 

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

This cycle is regulated by the computer clock using flip-flops in chain to delay the signal of the clock. This 
is done in that way to mitigate the effects of the intermediate states of the delay generated by the transitions between zero and one.

The chain flip-flops also creates a binary counter which can be used to control the phases of execution by incrementing the counter and using the output for a binary 
decoder.

Actually, this process is very complex, and CPU's can actually predict branches, execute instructions out of order and some other stuff to minimize idle time. 

---

## When does The OS Run

The OS is a process itself, and it runs whenever the CPU is not executing user code. It is loaded into memory when the computer boots and then can be invoked in several ways:

- **System Calls**: When a user program requests a service from the OS, such as file access or process management, it triggers a system call that switches the CPU to kernel mode to execute the OS code.
- **Interrupts**: Hardware devices can generate interrupts to signal the CPU that they require attention. When an enterrupt occurs, the CPU stops executing the current user program, stores the context and switches to the OS to handle the interrupt. This is build into the CPU architecture.
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

A **process** is an instance of a program with its own memory region.


### PCB 

The **process control block** is an abstraction the operating system uses to identify processes. 
An over simplification would be 

```rust 
pub struct PCB {
    pid: u16,
    state: Process_state,
    program_counter: u16,
    instruction_register: u8,
}

```

Processes from the perspective of the operating system require this structure to be handled by the context switching. This is also considered the 
CPU state of the process.


## IPC 

This stands for the term **inter process communication**. The two main approaches are **shared memory** and 
**message passing**. The first one is very simple because is just depends on telling the operating system that processes 
agree to use the memory region in an specific format. The preferred way is to use an specific region of memory of the OS address space 
to create a queue or queues in which data from the processes can be communicates can be communicated, this is the second approach.

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
is used by the operating system. The **user mode** is used for other programs which need the operating system or drivers to run. 

The value of the register is modified by an interrupt. 

The CPU contains a timer to automatically return control to the OS in the case a process does not voluntarily return control.

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

**Signals** are a way of inter-process communication. They are used to communicate a process an specific behavior like terminating, halting, 
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

This instruction is used to voluntarily give the CPU to another process for an specific time.
It uses an sleeping queue to regulate the use of the computer inner timer via software. 

--- 

## Race Conditions

Race conditions occur when multiple threads or processes access shared resources concurrently, and the final outcome depends on the timing of their execution. 

--- 

## Atomic Operations

Atomic operations are operations that are completed in a single step relative to other threads. They are indivisible and cannot be interrupted.

--- 

## Mutexes, Barriers and Condition Variables

- **Mutexes (mutual exclusions)** and condition variables are synchronization primitives used to manage access to shared resources in concurrent programming.
Mutexes provide a way to lock a resource so that only one thread can access it at a time, preventing race conditions.

- **Condition variables**: allow threads to wait for certain conditions to be met before continuing execution, enabling more complex synchronization patterns.

- **Barriers**: A barrier is an instruction which prevents the re-ordering of instructions in speculative 
execution.

Both approaches use **atomic operations** to ensure no race conditions occur.

The way this instructions are implemented is by combining barriers at the assembly level and atomic operations. In this way 
there is the guarantee that the atomic instruction happens in the right order.
---

## Cores 

Modern processors have multiple cpus which can improve performance both for processes and threads. This is handled by the 
operating system.

---

## Drivers 

A **driver** is a software made to communicate with hardware components. They make the development 
of the OS by regarding the specific software for all peripherals to the fabricants.

--- 

## GCC Compiler Process 

- Preprocessor: Inserts macros, eliminates comments etc. 
- Compiler: Generates the assembly code fromt the C file. 
- Assembler: Takes the assembly file and generates an object file which consists of headers and the binary machine structions. It is not executable. 
- Linker: Takes the object file/s and links them togethter to create an executable.

--- 

## Memory Mapped IO 

A way code can control hardware is via special region of memory which 
can not normally be accessed because of compiler optimizations unless the keyword `volatile` is used in `C`, for example.

- The region is assigned by the operating system which consists on input, output, control and status sectors. They way it 
is managed is via device drivers, to tell the operating system which sections are used in virtual memory for the management.

- This region of memory has special connections to the direct hardware or microcontroller of the device we want to control. Therefore, 
by writing specific values to it we can send signals which get decoded by the circuit and are translated into the reality as for example 
turning on pixel.

---

## Firmware 

It is embeded into the hardware. Nowadays it is called **UEFI** and before it was called **BIOS**. It loads the 
bootloaders and they also provide some functionality for configurations.

--- 

## Bootloaders 

It is responsible for launching the OS. It reads an specific sector in the disk to do this. 

--- 

## The Init Process

In unix systems there is a routine called `init()` which is used to be ran after the kernel is load into memory to load the first process 
which is in **user mode**. This process is also find as `systemd` or other init systems depending on how this has to behave. 

--- 

## Files 

A file, strictely speaking is sequence of bytes which represents data when read with an specific rules (program). It can be read or written to; in
some cases it can even be executed by the cpu as a programm.

In Unix, everything is treated like a file, which means that some regions of memory are dedicated for input and output. Even hardware components are 
viewed as file (Memory Map IO).

### File Format

A file is a set of rules which define how to parse a file. For example the first n-bytes until a line break represent different 
metadata (headers). Then with the information of the headers the file can be properly processed.

Typical formats:

- **Images**: JPEG, PNG GIF, WEBP, SVG.
- **Execs**: EXEC, MSI, APK, ELF4.
- **Document**: PDF, DOCS, TXT, Markdown.
- **Presentations**: PPTX, PDF.
- **Spreadsheet**: CSV, XLSX.
- **Video**: MP4, MKV, MOV, AVI.
- **Audio**: MP3, WAC M4A, FLAC.
- **Compressed**: ZIP, RAR, 7ZIP. 
- **Plain Text**: TXT, C, CPP, JSON, YAML, TOML, every programming language file.

--- 

## Character Encodings

These are ways of mapping bytes to characters. 

### ASCII

Supports only English characters plus punctuation, numbers and some special codes.

- Stores all characters in 7 bits.
- Wide used in systems.

The ASCII table looks like this

```

```

### Unicode

This is a universal standard for encoding all existing characters on earth plus emojis and way more.
It uses the concept of mapping **code points** to sequences of bytes. For example we could map a letter e with an accent 
to a singe byte or a the byte of e plus the byte of the accent.

The implementation depends on the algorithm.

The mapping is done is done from one **graphene** a unit of human writting to one or more code points.

### UTF-8

This version of **UTF** is a way of translating code points to 1 or 4 bytes.

--- 

## Memory Hirarchy 

--- 

## Data Corruption & Life Expectancy 

- **SSD**: The life expectancy can vary from 5 ot 10 years. They can retain data for up to 2 years if not powered on.

- **HDD**: They should last 4 to 7 years depending on the use, and enviroment. On the other side they can ratain data for at least 
20 years.

- **Flash Drive**: One year at max for both.

### Data Corruption Mitigation 

- Backups.
- Re-writing contents.

--- 

## API, ABI and ISA

- **API**: The application programming interface is a set of rules and definitions for using external applications or libraries. It defines  
how to use the external code via function calls, data structures, and protocols. We can also define our own API for our code to be used by other people.
As an example, when using any of the functions of the C standard library, we are using an API provided by the library.

- **ABI**: The application binary interface defines how different components of a binary program interact at the machine level. An example is 
the x86-64 ABI, which specifies how functions receive parameters, how the stack is managed, and how system calls are made on x86-64 architecture for intel and amd.

- **ISA**: The instruction set architecture is the set of instructions that a CPU can execute. It defines the machine language that the CPU understands. 
Examples include x86, ARM, and RISC-V.

--- 

## Base 64

**Base 64** is a binary-to-text encoding scheme that represents binary data in an ASCII string format. It is commonly used to encode 
data that needs to be stored and transferred over media that are designed to deal with textual data. This encoding helps ensure that 
the data remains intact without modification during transport.

### Encoding Process

Each group of three bytes (24 bits) from the binary data is divided into four groups of six bits. Each six-bit group is 
then mapped to a character in the Base 64 alphabet, which consists of 64 characters: A-Z, a-z, 0-9, +, and /. If the total number of 
bytes is not divisible by three, padding with one or two '=' characters is added to the end of the encoded string to make it a
multiple of four characters.

Example: 

| Plain | Binary | Triplets | Base 64 Alphabet|
|:------|--------|--------|---------|
| And   |01000001 01101110 01100100 |010000  010110  111001 100100|QW5k|