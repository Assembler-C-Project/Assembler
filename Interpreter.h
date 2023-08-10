#ifndef INTERPRETER_H
#define INTERPRETER_H
#define IS_COMMENT_EMPTY 0
#define IS_INSTRUCTION 1
#define IS_COMMAND 2

int divider(char *line, char **label, char **instruction, char **operands);
void remove_spaces(char *str);

#endif
