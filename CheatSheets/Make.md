# Makefiles

Makefiles are  used to automate the build process of `C`, `C++`, and other programming languages.
Flags, compiler options, and other build parameters can be specified in a `Makefile` to control the build process.

## Variables 

```make
CC=gcc
INCDIRS=I.
CFLAGS=... CFILES= x.c ...
BINARY=bin
```

## Buil Rules

**Build Rules** are used to programmatically define how our projects are going to be build

They start with the **name** followed by the `:`, then the target to be build and finally the dependencies that they have

```make
all: $(BINARY)
clean: rm -rf $(BINARY) $(*.o)
```


