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

idt.o: idt.c
	$(CC) $(CFLAGS) idt.c -o idt.o

pic.o: pic.c
	$(CC) $(CFLAGS) pic.c -o pic.o

idt_load.o: idt_load.asm
	$(ASM) -f elf32 idt_load.asm -o idt_load.o

io.o: io.c
	$(CC) $(CFLAGS) io.c -o io.o

irq.o: irq.asm
	$(ASM) -f elf32 irq.asm -o irq.o

kernel.bin: boot.o kernel.o idt.o pic.o idt_load.o irq.o io.o
	$(LD) $(LDFLAGS) boot.o kernel.o idt.o pic.o idt_load.o irq.o io.o -o kernel.bin


myos.iso: kernel.bin
	mkdir -p iso/boot
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o myos.iso iso/

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f *.o kernel.bin myos.iso