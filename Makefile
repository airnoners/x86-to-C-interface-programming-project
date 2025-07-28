# Compiler and assembler configuration
CC = gcc
ASM = nasm
CFLAGS = -O3 -Wall
ASMFLAGS = -f win64

# Targets
TARGET = bin/main.exe
ASM_OBJ = bin/asmfunc.obj
C_OBJ = bin/main.obj

all: $(TARGET)

$(TARGET): $(C_OBJ) $(ASM_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(C_OBJ): src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ): src/asmfunc.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f bin/*.obj bin/*.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
