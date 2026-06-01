section .multiboot
align 4

dd 0x1BADB002
dd 0
dd -(0x1BADB002)

global _start
extern kernel_main

section .text
bits 32

_start:
    call kernel_main

.hang:
    jmp .hang
