#ifndef SHELL_H
#define SHELL_H

extern int prompt_row;
extern int prompt_col;
extern char command[256];
extern int cmd_index;

void exec_cmd(const char *cmd);

#endif
