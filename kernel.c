#include "idt.h"
#include "pic.h"
#include "io.h"

char* video = (char*)0xB8000;

int row = 0;
int col = 0;

char keyboard_map[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
};

// void keyboard_handler(){
//   unsigned char scancode = inb(0x60);

//   outb(0x20,0x20);
// }

int position(int row,int col){
  return ((row*80)+col)*2;
}

void clearRow(int row){
  for(int i=0;i<80;i++){
    int pos = position(row,i);
    video[pos] = ' ';
    video[pos+1] = 0x07;
  }
}

void scroll(){
  for(int row=1;row<25;row++){
    for(int col=0;col<80;col++){
      int from = position(row,col);
      int to = position(row-1,col);
      video[to] = video[from];
      video[to+1] = video[from+1];
    }
  }
  clearRow(24);
  row = 24;
}

void putchar(char c){
  if(c == '\n'){
    col = 0;
    row++;
    return;
  }
  if(col>=80){
    col = 0;
    row++;
  }
  if(row>=25){
    scroll();
  }
  int pos = position(row,col);
  video[pos] = c;
  video[pos+1] = 0x07;
  col++;
}

void print(const char* s){
  while(*s){
    putchar(*s++);
  }
}

void timer_handler()
{
    outb(0x20, 0x20);
}

void keyboard_handler(){
  unsigned char scancode = inb(0x60);
  if(scancode < 128){
    char c = keyboard_map[scancode];
    if(c){
      putchar(c);
    }
  }
  outb(0x20,0x20);
}

void kernel_main(){
  idt_init();
  pic_remap();
	asm volatile ("sti");
  print("Hello, World!\n");
	while(1){
    
  };
}
