# Makefile for chess.c

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

# Target executable
TARGET = out
SRC = chess.c

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up
clean:
	rm -f $(TARGET)
