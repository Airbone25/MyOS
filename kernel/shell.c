#include "shell.h"
#include "vga.h"
#include "string.h"
#include "io.h"

int prompt_row;
int prompt_col;
char command[256];
int cmd_index = 0;

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
