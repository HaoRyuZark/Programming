# Buffer Overflow

**Buffer overflows** occur when a program writes more data to a region of memory, or buffer, than it was allocated to hold. 
Such a simple error, can be exploited by injection malicious code into the memory space of the application, corrupting data, 
crashing the program etc.

--- 

## Simple C Example 

```c 
#include <stdio.h>
#include <unistd.h>

int main () {

    char buffer[200];
    int input = read(0, buffer, 400); // we allowing more than we have
    printf("You entered: %s\n", buffer);
    return 0;
}
```

--- 

## Preliminary Steps

1. Find the vulnerable function in the code.

2. Determine the size of the buffer and how much data can be written to it.

3. Find the EIP-offset (the number of bytes needed to overwrite the return address).

4. Use the eip-value to check if we can overwrite the return address by sending a payload of some size.

5. Exploit in the desired way. 

--- 

## Code Injection 

If we manage to overwrite the return address of a function, we can redirect the flow of execution to our injected code.
For example, if we have a function that looks like this:

```c 
void vulnerable_function() {
    char buffer[100];
    gets(buffer); // unsafe function
}
``` 




--- 
