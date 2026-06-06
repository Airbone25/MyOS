ASM=nasm
CC=gcc
LD=ld

CFLAGS=-m32 -ffreestanding -c -Iinclude
LDFLAGS=-m elf_i386 -T linker.ld

MODULES=boot kernel cpu drivers
OBJ_DIR=obj

# Find all C and ASM files
C_SOURCES=$(shell find $(MODULES) -name '*.c')
ASM_SOURCES=$(shell find $(MODULES) -name '*.asm')

# Convert source file names to object file names
C_OBJECTS=$(patsubst %.c, $(OBJ_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS=$(patsubst %.asm, $(OBJ_DIR)/%.o, $(ASM_SOURCES))
OBJECTS=$(C_OBJECTS) $(ASM_OBJECTS)

# The bootloader usually needs to be linked first, or the linker script handles it.
# We will just pass $(OBJECTS) to ld, but we'll ensure the linker.ld takes care of ENTRY.

all: myos.iso

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(@D)
	$(ASM) -f elf32 $< -o $@

kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.bin

myos.iso: kernel.bin
	mkdir -p iso/boot
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o myos.iso iso/

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf $(OBJ_DIR) kernel.bin myos.iso