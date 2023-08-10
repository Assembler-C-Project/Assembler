# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -ansi -pedantic

# Source files
SRCS := decoder.c functions.c Interpreter.c PreAssem.c main.c

# Object files
OBJS := $(SRCS:.c=.o)

# Header files directory
INCDIR := include

# Executable name
EXECUTABLE := assembler

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

clean:
	rm -f $(EXECUTABLE) $(OBJS)
