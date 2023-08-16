/*interpreter.c
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: defines constants and functions used in an interpreter program for handling different types of lines in assembly code. The constants represent line types (comments, instructions, and commands), while the functions split lines into parts and remove unnecessary spaces, tabs, and newlines from strings. This header file aids in organizing and maintaining the interpreter's functionality. */
#ifndef INTERPRETER_H
#define INTERPRETER_H

/* Define constants for different line types */
#define IS_COMMENT_EMPTY 0
#define IS_INSTRUCTION 1
#define IS_COMMAND 2

/* Function declarations */
int divider(char *line, char **label, char **instruction, char **operands);
void remove_spaces(char *str);

#endif
