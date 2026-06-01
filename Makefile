ASM=nasm
CC=gcc
LD=ld

CFLAGS=-m32 -ffreestanding -c
LDFLAGS=-m elf_i386 -T linker.ld

all: myos.iso

boot.o: boot.asm
	$(ASM) -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c -o kernel.o

kernel.bin: boot.o kernel.o
	$(LD) $(LDFLAGS) boot.o kernel.o -o kernel.bin

myos.iso: kernel.bin
	mkdir -p iso/boot
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o myos.iso iso/

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f *.o kernel.bin myos.iso
