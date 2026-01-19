CC = gcc 
CFLAGS = -Wall -Wextra
SRC = src/main.c 
TARGET = bin/server 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(TARGET)

.PHONY: all run clean server build-and-run
