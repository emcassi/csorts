# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -std=c17 -Wall -Wextra -pedantic -O2 `sdl2-config --cflags`

# Executable Name
EXEC = csorts

# Linker Flags
LDFLAGS = `sdl2-config --libs`

# Source Files
SOURCES = $(wildcard *.c)

# Object Files
OBJECTS = $(SOURCES:.c=.o)

# Default Make
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compiling every source file
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Cleaning everything that can be automatically recreated
clean:
	rm -f $(EXEC) $(OBJECTS)

.PHONY: all clean
