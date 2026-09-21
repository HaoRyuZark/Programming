
// gcc -static -nostdlib hello_world_no_lib.c -o hello
int _start(void) {
    const char hello_world[14] = "Hello, World!\0";
    
    asm volatile(
    "mov $1, %%rax\n\t" // syscall num for write
    "mov $1, %%rdi\n\t" // stdoout (fd = 1)
    "lea %0, %%rsi\n\t" // address of the string
    "mov $14, %%rdx\n\t" // length
    "syscall\n\t"
    : 
    : "m"(hello_world) 
    : "%rax", "%rdi", "%rsi", "%rdx"
    );
    // Exit syscall 

    asm volatile(
    "mov $60, %%rax\n\t" // SYS_EXIT
    "mov $0, %%rdi\n\t" // exit code 0
    "syscall\n\t"
    :::"%rax", "%rdi"
    );
    
    // never called since we exit before
    return 0;
}
