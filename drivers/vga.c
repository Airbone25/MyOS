#include "vga.h"
#include "shell.h"

char *video = (char *)0xB8000;
int row = 0;
int col = 0;

int position(int row, int col){
  return ((row * 80) + col) * 2;
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

void clearRow(int r){
  for (int i = 0; i < 80; i++){
    int pos = position(r, i);
    video[pos] = ' ';
    video[pos + 1] = 0x07;
  }
}

void scroll(){
  for (int r = 1; r < 25; r++){
    for (int c = 0; c < 80; c++){
      int from = position(r, c);
      int to = position(r - 1, c);
      video[to] = video[from];
      video[to + 1] = video[from + 1];
    }
  }
  clearRow(24);
  row = 24;
}

void clear_screen(){
  for (int r = 0; r < 25; r++){
    clearRow(r);
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
