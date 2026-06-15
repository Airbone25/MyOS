#include "keyboard.h"
#include "io.h"
#include "vga.h"
#include "shell.h"

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
