# Systems Programming

Systems programming involves writing software that provides services to the computer hardware. This includes operating systems, device drivers, and other low-level software that interacts directly with the hardware. To understand systems programming, one must be familiar with the architecture of the computer, including how memory is managed, how processes are scheduled, and how input/output operations are performed. This document covers low level concepts which are essential for systems programming.

## Size of Variables

In contrast to high-level languages, low-level languages like C allow you to control the size of variables explicitly. The size of a variable can affect performance and memory usage. Here are some common variable sizes in C:

- `char`: 1 byte
- `short`: 2 bytes
- `int`: 4 bytes
- `long`: 4 or 8 bytes (depending on the architecture)
- `float`: 4 bytes
- `double`: 8 bytes

By understanding the size of different data types, you can make informed decisions about memory allocation and optimize your programs for better performance.

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

## Pointers

Pointers are a fundamental concept in low-level programming. They allow you to directly manipulate memory addresses, which is crucial for performance and resource management. A pointer is a variable that stores the address of another variable.

Example of using pointers in C:

```C

#include <stdio.h>
int main() {

int var = 42;
    
    int* ptr = &var;

    printf("Value of var: %d\n", var);
    printf("Address of var: %p\n", (void *)&var);
    printf("Value of ptr: %p\n", (void *)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);

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

## Casting String-numbers to Numbers 

Multiple programming languages have defaults for converting string to numbers. The way this functionality works is by 
using the ASCII enconding which for the digits starts at 48. Therefore to convert a character number to a number the computer 
subtracts 48 from the binary code of the character. For multiple numbers with multiple digits a system for the positions has to be accounted.

## The Stack

Is a memory region that stores local variables, function parameters, and return addresses. It operates in a last-in, first-out (LIFO) manner. The data is stored contiguously, and the stack grows downwards in memory. Each function call creates a new stack frame that contains the function's local variables and parameters.

## The Heap

The heap is a memory region used for dynamic memory allocation. Unlike the stack, memory in the heap is managed manually by the programmer using functions like `malloc`, `calloc`, `realloc`, and `free`. The heap allows for more flexible memory usage, but it also requires careful management to avoid memory leaks and fragmentation. The heap is considered slower than the stack for memory allocation and deallocation because it involves more complex bookkeeping. This slowness is caused by the fragmentation of the memory.

## Cache

Cache is a small, fast memory located close to the CPU that stores frequently accessed data. It helps speed up data retrieval by reducing the time it takes to access data from the main memory (RAM).

When the requested data is found in the cache, it is called a cache hit; if not, it is a cache miss, and the data must be fetched from the slower main memory. There is
a caching hierarchy, typically consisting of multiple levels (L1, L2, L3), with L1 being the fastest and smallest, and L3 being larger but slower. If data is not used frequently, it may be evicted from the cache to make room for new data.

## System Calls

System calls are the interface between user applications and the operating system kernel. They allow user programs to request services from the kernel, such as file operations, process management, and network communication. System calls provide a controlled way for applications to interact with hardware and system resources.

## Fetch Decode Execute Cycle

The fetch-decode-execute cycle is the fundamental process by which a CPU executes instructions. It consists of three main stages:

1. **Fetch**: The CPU retrieves an instruction from memory, typically from the instruction cache or main memory, using the program counter (PC) to determine the address of the next instruction.
2. **Decode**: The fetched instruction is decoded to determine what operation it specifies and which operands are involved. This step involves interpreting the binary representation of the instruction.
3. **Execute**: The CPU performs the operation specified by the instruction, which may involve arithmetic or logical operations, memory access, or control flow changes. The results of the execution are then stored back in memory or in registers.
4. **Repeat**: The cycle repeats for the next instruction, with the program counter being updated to point to the next instruction in the sequence.

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

---

## When does The OS Run

The OS is a process itself, and it runs whenever the CPU is not executing user code. It is loaded into memory when the computer boots and then can be invoked in several ways:

- **System Calls**: When a user program requests a service from the OS, such as file access or process management, it triggers a system call that switches the CPU to kernel mode to execute the OS code.
- **Interrupts**: Hardware devices can generate interrupts to signal the CPU that they require attention. When an interrupt occurs, the CPU stops executing the current user program, stores the context and switches to the OS to handle the interrupt. This is build into the CPU architecture.
- **Exceptions**: These are unexpected events that occur during program execution, such as division by zero or invalid memory access. When an exception occurs, the CPU switches to the OS to handle the error.
- **Context Switching**: The OS can preempt a running user program to give CPU time to another process. This is done through context switching, where the OS saves the state of the current process and loads the state of the next process to be executed.

## Memory Layout of a Process

The memory layout of a process typically consists of several segments:

- **Text Segment**: Contains the executable code of the program.
- **Data Segment**: Contains global and static variables.
- **BSS Segment**: Contains uninitialized global and static variables.
- **Heap Segment**: Used for dynamic memory allocation.
- **Stack Segment**: Contains local variables and function call information.

## Virtual Memory

Virtual memory is a memory management technique that allows a computer to use more memory than is physically available by using disk space as an extension of RAM. It also provides the illusion of a large, contiguous memory space to applications, while the operating system manages the mapping between virtual addresses and physical addresses.

It is done by dividing the memory into fixed-size pages and mapping them to physical memory frames. When a program accesses a page that is not currently in physical memory, a page fault occurs, and the OS retrieves the required page from disk and updates the mapping.

Via hardware support, such as the Memory Management Unit (MMU), virtual memory allows for efficient memory usage, isolation between processes, and protection against unauthorized access. This unit is also responsible for managing the page table, which keeps track of the mapping between virtual addresses and physical addresses.

## ABI

The Application Binary Interface (ABI) defines how different components of a binary program interact at the machine level. It specifies details such as calling conventions, data types, and system calls, ensuring that compiled code can run on a specific platform without requiring recompilation.

## Processes

A **proces** is an instance of a program.

## PCB 

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

## Interrupts

Interrupts are implemented at hardware level to store the state of the CPU correctly. One variant is to use 
two register sets. One for the user mode and one for the kernel mode. 

Another way is to make the stack register of the OS always visible to the CPU via a hardwired memory location or register. So 
during the context switching the all critical registers can be stored correctly.

## User Mode and Kernel Mode

The mode bit is an special register which allows the cpu to execute privileged instructions. This mode is called **kernel mode**, and 
is used by the operating system. The **user mode** is used for other programms which need the operating system or drivers to run. 

The value of the register is modified by an interrupt. 

The CPU contains a timer to automatically return control to the OS in the case a process does not voluntarelly return control.

## CPU Scheduling

CPU scheduling is the process of deciding which of the processes in the ready queue will be allocated to the CPU. The primary motivation behind CPU scheduling is to maximize CPU utilization and provide a responsive system for users. A well-designed scheduling algorithm aims to ensure that the CPU is never idle as long as there are processes ready to run, while also providing a fair and efficient allocation of CPU time among competing processes. Scheduling is a fundamental concept in multiprogramming operating systems, where multiple processes can reside in memory at the same time. The scheduler is a key component of the operating system that makes these allocation decisions.

## Cooperative and Preemptive Scheduling

There are two main approaches to CPU scheduling: cooperative and preemptive.

- Cooperative scheduling relies on a process to voluntarily give up the CPU. A running process will continue to use the CPU until it either terminates or explicitly yields the CPU. This type of scheduling is simple to implement but can lead to a system becoming unresponsive if a single process enters an infinite loop or a long computation without yielding. In such a scenario, no other processes would get a chance to run.

- Preemptive scheduling is a more robust approach where the operating system can interrupt a running process and force it to give up the CPU. This is typically done after a certain time interval, known as a time slice, has elapsed, or when a higher-priority process becomes ready. Preemptive scheduling ensures that no single process can monopolize the CPU, leading to a more responsive and fair system. It is the dominant approach in modern operating systems.

## Scheduling Strategies

Several algorithms and strategies are used to implement CPU scheduling, each with its own advantages and disadvantages. The choice of strategy often depends on the goals of the system (e.g., maximizing throughput, minimizing response time, or ensuring fairness).

- **First-Come, First-Served (FCFS)**: This is the simplest scheduling algorithm, where processes are executed in the order they arrive in the ready queue. FCFS is a non-preemptive algorithm that is easy to implement but can result in a phenomenon called the convoy effect, where a long-running process at the front of the queue can cause all subsequent processes to wait, leading to poor average waiting times.

- **Shortest-Job-Next (SJN)**: This algorithm selects the process with the smallest estimated execution time to run next. SJN can be either preemptive (Shortest Remaining Time First) or non-preemptive. It is an optimal algorithm for minimizing the average waiting time, but it has a major drawback: it requires knowing the future execution time of a process, which is impossible in practice. In practice, this is often estimated based on past behavior.

- **Priority Scheduling:** This strategy assigns a priority level to each process, and the CPU is allocated to the process with the highest priority. Priority can be based on factors such as process type, memory requirements, or the user who initiated it. A key problem with priority scheduling is starvation, where a low-priority process may never get to run if there is a continuous stream of high-priority processes. This can be mitigated through a technique called aging, where the priority of a process increases over time.

- **Round-Robin (RR) Scheduling:** This is a preemptive algorithm designed for time-sharing systems. Each process is given a small unit of CPU time, called a time quantum or time slice. When the time quantum expires, the process is preempted and added to the end of the ready queue. RR provides a fair share of the CPU to each process and is generally effective for interactive systems where response time is a key concern. The performance of RR is highly dependent on the size of the time quantum. A small quantum can lead to frequent context switches, which can increase overhead, while a large quantum can make it behave like FCFS.

## Signals 

**Signals** are a way of inter-process communication. They are used to communicate a process an specific behaviour like terminating, halting, 
resuming etc. They are provided the OS to trigger interrupts directly.

## Concurrency And parallelism

Concurrency and parallelism are two related concepts in computer science that deal with the execution of multiple tasks simultaneously.

- **Concurrency** refers to the ability of a system to handle multiple tasks at the same time, but not necessarily executing them simultaneously. It involves managing multiple tasks that may be in progress at the same time, allowing for better resource utilization and responsiveness. This is done on a single CPU core by interleaving the execution of tasks, giving the illusion that they are running simultaneously.

- **Parallelism** on the other hand, involves executing multiple tasks simultaneously, typically on multiple CPU cores or processors. This can lead to significant performance improvements for compute-intensive tasks. In contrast to concurrency, parallelism requires multiple processing units to execute tasks at the same time, effectively dividing the workload among them.

- **Address Space**  is the memory region used by a process.

## Threads

Threads are inner entities in a process which can be executed concurrently inside a process. They have their own CPU state and are 
handled via syscalls for creation, deletion and execution. When the OS changes from the one process to another it will excute the 
threads which are not sleeping.

From the OS perspective a thread is not very different from a process but for a developer it is 
way to inform the operating system that specific regions of a program can be executed concurrently.

## Memory protection

Because checking for memory security each time a processes is executed would be very costly in terms of performance this ascpect is implemented via hardware.

The condition is: **address >= base and address < base + limit**

## Sleep 

This instruction is used to voluntarelly give the CPU to another process for an specific time.
It uses an sleeping queue to regulate the use of the computer inner timmer via software. 

## Race Conditions

Race conditions occur when multiple threads or processes access shared resources concurrently, and the final outcome depends on the timing of their execution. This can lead to unpredictable behavior and bugs in the program. It is important to note that spanning multiple threads does not guarantee parallel execution, as the operating system may schedule them on a single core, leading to interleaved execution. But this can still result in race conditions if not properly managed.

## Atomic Operations

Atomic operations are operations that are completed in a single step relative to other threads. They are indivisible and cannot be interrupted, ensuring that no other thread can see an intermediate state. This is crucial for preventing race conditions and ensuring data consistency in concurrent programming. The mostly consist of simple operations like incrementing a counter or setting a flag, and they are typically implemented using low-level hardware instructions that guarantee atomicity.

## Mutexes and Condition Variables

Mutexes (mutual exclusions) and condition variables are synchronization primitives used to manage access to shared resources in concurrent programming. Mutexes provide a way to lock a resource so that only one thread can access it at a time, preventing race conditions.

Condition variables allow threads to wait for certain conditions to be met before continuing execution, enabling more complex synchronization patterns.

Both approaches use **atomic operations** to ensure no race conditions occur.

## Cores 

Moder processors have multiple cpus which can improve performance both for processes and threads. This is handled by the 
operating system.

## Drivers 

A **driver** is a software made to communicate with hardware components. They make the development 
of the OS by regarding the specific software for all peripherals to the fabricants.
