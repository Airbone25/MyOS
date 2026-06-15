section .multiboot
align 4

MBALIGN equ 1 << 0
MEMINFO equ 1 << 1

FLAGS equ MBALIGN | MEMINFO

dd 0x1BADB002
dd FLAGS
dd -(0x1BADB002 + FLAGS)

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KB
stack_top:

section .data
align 8
gdt_start:
    dq 0x0000000000000000 ; null descriptor
    dq 0x00cf9a000000ffff ; 32-bit code, 0-4GB
    dq 0x00cf92000000ffff ; 32-bit data, 0-4GB
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start

global _start
extern kernel_main

section .text
bits 32

_start:
    lgdt [gdt_ptr]
    jmp 0x08:.flush_cs

.flush_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, stack_top
    push ebx
    push eax
    call kernel_main

.hang:
    jmp .hang
