# Makefiles

Makefiles are  used to automate the build process of `C`, `C++`, and other programming languages.
Flags, compiler options, and other build parameters can be specified in a `Makefile` to control the build process.

## Variables 

We can use Variables to store commands, list of files etc.

```make
CC=gcc
INCDIRS=I.
CFLAGS=... CFILES= x.c ...
BINARY=bin
RM= rm -f
```

## Build Rules

**Build Rules** are used to programmatically define how our projects are going to be build

 - Structure:

```make
target: $(dependencies)
    commands
```

- Example:

```make
all: $(NAME)

example: a.c b.c c.c 
gcc a.c b.c c.c -o myprog 

$(NAME): $(OBJ)
$(ARD) $@ $^
```

**$@ $^** The first represents the name of the output file and the second the list of all dependencies

## Clean 

```make
.PHONY : clean 
clean: 
    rm -f *.o myprog
```

## Patterns 

```make
%.o : %.c 
    gcc -c $(FLAGS) $< -o $@
```

**$<** represents the name of the source file.

## Backslash 

We can use `\` to split lines like in `C` macros.


## GCC Cheatsheet

### Basic Compilation Commands

- **Compile a C file**
  ```sh
  gcc file.c -o output
  ```
- **Compile and run in one command**
  ```sh
  gcc file.c -o output && ./output
  ```
- **Compile a C++ file**
  ```sh
  g++ file.cpp -o output
  ```

### Compilation Modes

- **Compile without linking** (generate object file)
  ```sh
  gcc -c file.c
  ```
- **Compile multiple files**
  ```sh
  gcc file1.c file2.c -o output
  ```
- **Compile and link separately**
  ```sh
  gcc -c file1.c
  gcc -c file2.c
  gcc file1.o file2.o -o output
  ```

### Optimization Levels

- **No optimization**
  ```sh
  gcc -O0 file.c -o output
  ```
- **Basic optimization**
  ```sh
  gcc -O1 file.c -o output
  ```
- **More optimization**
  ```sh
  gcc -O2 file.c -o output
  ```
- **Full optimization**
  ```sh
  gcc -O3 file.c -o output
  ```
- **Optimize for size**
  ```sh
  gcc -Os file.c -o output
  ```

### Debugging Options

- **Enable debugging symbols**
  ```sh
  gcc -g file.c -o output
  ```
- **Enable all warnings**
  ```sh
  gcc -Wall file.c -o output
  ```
- **Enable extra warnings**
  ```sh
  gcc -Wextra file.c -o output
  ```
- **Treat warnings as errors**
  ```sh
  gcc -Werror file.c -o output
  ```

### Linking Libraries

- **Link a math library (libm)**
  ```sh
  gcc file.c -o output -lm
  ```
- **Link a custom library**
  ```sh
  gcc file.c -o output -L/path/to/lib -lname
  ```
  (If the library file is `libname.so` or `libname.a`)

### Preprocessor Options

- **Only run the preprocessor**
  ```sh
  gcc -E file.c -o output.i
  ```
- **Define a macro**
  ```sh
  gcc -DDEBUG file.c -o output
  ```

### Assembly and Machine Code

- **Generate assembly code**
  ```sh
  gcc -S file.c -o file.s
  ```
- **Generate machine code**
  ```sh
  gcc -c file.c -o file.o
  ```

### Cross-Compilation

- **Specify target architecture**
  ```sh
  gcc --target=<arch> file.c -o output
  ```
- **Example for ARM**
  ```sh
  arm-linux-gnueabi-gcc file.c -o output
  ```

### Miscellaneous Options

- **Show include paths**
  ```sh
  gcc -v file.c -o output
  ```
- **Check for compilation without generating an output file**
  ```sh
  gcc -fsyntax-only file.c
  ```
- **Enable position-independent code (for shared libraries)**
  ```sh
  gcc -fPIC file.c -o output
  ```
- **Create a shared library**
  ```sh
  gcc -shared -o libname.so file.c
  ```



