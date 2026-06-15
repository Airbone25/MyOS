#ifndef VGA_H
#define VGA_H

extern char *video;
extern int row;
extern int col;

int position(int row, int col);
void backspace();
void clearRow(int row);
void scroll();
void clear_screen();
void putchar(char c);
void print(const char *s);

#endif
