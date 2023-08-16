/*decoder.h
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: The purpose of this code is to define the header file "decoder.h" which contains declarations for structures representing commands and instructions */
#ifndef DECODER_H
#define DECODER_H

/* Define the maximum length of a line */
#define MAX_LINE_LENGTH 80

/* Include necessary header files */
#include "functions.h"
#include "Interpreter.h"

/* Define a structure to represent a command */
typedef struct cmd {
    char *name;      /* The name of the command */
    int value;       /* The associated value of the command */
} cmd;

/* Declare an array of command structures */
extern cmd cmds[16];

/* Define a structure to represent an instruction */
typedef struct inst {
    char *name;      /* The name of the instruction */
    int value;       /* The associated value of the instruction */
} inst;

/* Declare an array of instruction structures */
extern inst insts[4];

/* Function prototypes */

/* Decode a line of code */
int decoder(char *line, int line_num, int *IC, int *DC, char ***base64Chars, mem_word **label_lst, char *filename);

/* Run the decoder on a source file */
void RunDecoder(FILE *SourceFile, char *fileName);

#endif
