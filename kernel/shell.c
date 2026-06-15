#include "shell.h"
#include "vga.h"
#include "string.h"
#include "io.h"
#include "multiboot.h"
#include "memory.h"

int prompt_row;
int prompt_col;
char command[256];
int cmd_index = 0;

char hex[] = "0123456789ABCDEF";

void print_hex32(uint32_t num)
{
    for(int i = 28; i >= 0; i -= 4)
    {
        putchar(hex[(num >> i) & 0xF]);
    }
}

void exec_cmd(const char *cmd){
  if (strcmp(cmd, "version") == 0){
    print("MyOS 0.1\n");
  }else if(strcmp(cmd, "help") == 0){
    print("Available commands:\n");
    print("version - Show OS version\n");
    print("help - Show this help message\n");
  }else if(strcmp(cmd, "clear") == 0){
    clear_screen();
  }else if(strcmp(cmd, "reboot") == 0){
    outb(0x64, 0xFE);
  }else if(strcmp(cmd, "") == 0){
    print("");
  }else if(strcmp(cmd, "memmap") == 0){
    for(int i=0;i<memory_region_count;i++){
        print("Region ");
        print_hex32(i);
        print("\n");

        print("Base: ");
        print_hex32((uint32_t)memory_map[i].base);
        print("\n");

        print("Length: ");
        print_hex32((uint32_t)memory_map[i].length);
        print("\n");

        print("Type: ");
        print_hex32(memory_map[i].type);
        print("\n\n");
    }
  }
  else{
    print("Unknown command: ");
    print(cmd);
    print("\n");
  }
  print("MyOS> ");
  prompt_row = row;
  prompt_col = col;
}
