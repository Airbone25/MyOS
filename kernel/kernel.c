#include "idt.h"
#include "pic.h"
#include "vga.h"
#include "shell.h"

void kernel_main(){
  idt_init();
  pic_remap();
  asm volatile("sti");
  print("MyOS> ");
  prompt_row = row;
  prompt_col = col;
  while (1);
}
