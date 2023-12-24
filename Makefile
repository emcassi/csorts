#OBJECTS Compiler
CC = gcc

# Compiler Flags
CFLAGS = -std=c17 -Wall -Wextra -pedantic -O2 `sdl2-config --cflags`

# Debug Flags
DEBUGFLAGS = -g

# Executable Name
EXEC = csorts

# Linker Flags
LDFLAGS = `sdl2-config --libs`

# Source Files
SOURCES = $(wildcard *.c)

# Object Files
OBJECTS = $(SOURCES:.c=.o)

# Debug Object Files
DEBUG_OBJECTS = $(SOURCES:.c=.debug.o)

# Test Executable File
TEST_EXEC = test

# Default Make
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compiling every source file
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Debug build
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(EXEC)

test:
	gcc -o test $(SOURCES) tests/test1.c tests/barlist_test.c -lcunit

# Compiling every source file with debug information
%.debug.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUGFLAGS)

# Cleaning everything that can be automatically recreated
clean:
	rm -f $(EXEC) $(OBJECTS) $(DEBUG_OBJECTS) $(TEST_EXEC)

.PHONY: all clean debug
