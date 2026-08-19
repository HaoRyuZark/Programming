# Makefiles

**Makefiles** are  used to automate the build process of `C`, `C++`, and other programming languages.
Flags, compiler options, and other build parameters can be specified in a `Makefile` to control the build process.

The main idea is to define rules and order of compilation via variables and rules instead of writting our own build scripts from scratch.

--- 

## Variables 

We can use Variables to store commands, list of files etc.

```make
CC=gcc
INCDIRS=I.
CFLAGS=... CFILES= x.c ...
BINARY=bin
RM= rm -f
```

--- 

## Build Rules

**Build Rules** are used to programmatically define how our projects are going to be build

 - Structure:

```make
target: $(dependencies)
    commands
```

- Example:

```make

OBJ= a.o b.o c.o
BINARY=bin 

all: $(BINARY)

example: a.c b.c c.c 
gcc a.c b.c c.c -o myprog 

$(BINARY): $(OBJ)
$(ARD) $@ $^
```

`$@ $^` The first represents the name of the output file and the second the list of all dependencies

--- 

## Clean 

```make
.PHONY : clean 
clean: 
    rm -f *.o myprog
```

--- 

## Rule For Creating Object Files From Each C File

```make 
%.o: %.c 
    $(CC) $(FLAGS) -c -o $@ $^
```

--- 

## Patterns 

```make
%.o : %.c 
    gcc -c $(FLAGS) $< -o $@
```

**$<** represents the name of the source file.

---

