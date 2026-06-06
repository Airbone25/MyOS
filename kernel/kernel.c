#include "idt.h"
#include "pic.h"
#include "io.h"

char *video = (char *)0xB8000;

int row = 0;
int col = 0;

int prompt_row;
int prompt_col;

char command[256];
int cmd_index = 0;

char keyboard_map[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
    [0x20] = 'd',
    [0x12] = 'e',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x17] = 'i',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x32] = 'm',
    [0x31] = 'n',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x10] = 'q',
    [0x13] = 'r',
    [0x1F] = 's',
    [0x14] = 't',
    [0x16] = 'u',
    [0x2F] = 'v',
    [0x11] = 'w',
    [0x2D] = 'x',
    [0x15] = 'y',
    [0x2C] = 'z',
    [0x39] = ' ',
    [0x1C] = '\n',
    [0x0E] = '\b',
};

int strcmp(const char *a, const char *b){
  while (*a && *b){
    if (*a != *b)
      return *a - *b;
    a++;
    b++;
  }
  return *a - *b;
}

void backspace(){
  if (row == prompt_row && col == prompt_col){
    return;
  }
  if (col > 0){
    col--;
    int pos = position(row, col);
    video[pos] = ' ';
    video[pos + 1] = 0x07;
  }
  if (cmd_index > 0){
    cmd_index--;
    command[cmd_index] = '\0';
  }
}

int position(int row, int col){
  return ((row * 80) + col) * 2;
}

void clearRow(int row){
  for (int i = 0; i < 80; i++){
    int pos = position(row, i);
    video[pos] = ' ';
    video[pos + 1] = 0x07;
  }
}

void scroll(){
  for (int row = 1; row < 25; row++){
    for (int col = 0; col < 80; col++){
      int from = position(row, col);
      int to = position(row - 1, col);
      video[to] = video[from];
      video[to + 1] = video[from + 1];
    }
  }
  clearRow(24);
  row = 24;
}

void clear_screen(){
  for (int row = 0; row < 25; row++){
    clearRow(row);
  }
  row = 0;
  col = 0;
}

void putchar(char c){
  if (c == '\n'){
    col = 0;
    row++;
    return;
  }
  if (c == '\b'){
    backspace();
    return;
  }
  if (col >= 80){
    col = 0;
    row++;
  }
  if (row >= 25){
    scroll();
  }
  int pos = position(row, col);
  video[pos] = c;
  video[pos + 1] = 0x07;
  col++;
}

void print(const char *s){
  while (*s){
    putchar(*s++);
  }
}

void timer_handler(){
  outb(0x20, 0x20);
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

void keyboard_handler(){
  unsigned char scancode = inb(0x60);

  if (scancode < 128){
    char c = keyboard_map[scancode];

    if (c == '\n'){
      putchar('\n');

      command[cmd_index] = '\0';
      exec_cmd(command);
      cmd_index = 0;
    }
    else if (c == '\b'){
      putchar('\b');
    }
    else if (c){
      if (cmd_index < 255){
        command[cmd_index++] = c;
      }
      putchar(c);
    }
  }

  outb(0x20, 0x20);
}

void kernel_main(){
  idt_init();
  pic_remap();
  asm volatile("sti");
  print("MyOS> ");
  prompt_row = row;
  prompt_col = col;
  while (1);
}
