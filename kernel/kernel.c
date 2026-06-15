#include "idt.h"
#include "pic.h"
#include "vga.h"
#include "shell.h"
#include "memory.h"
#include "multiboot.h"

void kernel_main(unsigned long magic, unsigned long addr){
  idt_init();
  pic_remap();
  multiboot_info_t *mbi = (multiboot_info_t *)addr;
  // read memory map from multiboot info
  if(!(mbi->flags & (1 << 6))){
    print("No memory map!\n");
    while(1);
  }
  multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
  while((uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length){
    if(memory_region_count < MAX_MEMORY_REGIONS){
      memory_map[memory_region_count].base = mmap->addr;
      memory_map[memory_region_count].length = mmap->len;
      memory_map[memory_region_count].type = mmap->type;
      memory_region_count++;
    }
    mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
  }
  asm volatile("sti");
  print("MyOS> ");
  prompt_row = row;
  prompt_col = col;
  while (1);
}
