/*functions.h
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: define various utility functions, data structures, and constants that are used in an assembly language decoder program, including error code enumeration, register mappings, label node structure, memory word structure, and function prototypes for operations related to validating labels, operand division, data searching, binary conversion, file handling, and file deletion.*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "states.h"

/* Define constants */
#define NUM_OF_REGS 8
#define END_OF_BIN -3000
#define IMMEDIATE_MAPPING 1
#define DIRECT_MAPPING 3
#define DIRECT_REG_MAPPING 5

#define OPCODE_SHIFT 5
#define SOURCE_OPERAND_SHIFT 9
#define DESTINATION_OPERAND_SHIFT 2

#define SOURCE_REG_SHIFT 7
#define DESTINATION_REG_SHIFT 2
#define IS_DATA 16
#define IS_STRING 17
#define IS_ENTRY 18
#define IS_EXTERN 19

/* Define enumeration for error codes */
enum error_code {
    ERR_2_OPS,
    ERR_1_OP,
    ERR_0_OP,
    ERR_DEST_TYPE,
    ERR_SRC_TYPE,
    ERR_INV_LABEL,
    ERR_INV_CMD,
    ERR_INV_ENT,
    ERR_VAR_NF,
    ERR_INV_REG,
    ERR_INV_NUM
};

/* Define a structure for error types */
typedef struct ErrorType {
    int num;
    char *message;
} ErrorType;

/* Declare an external array of error types */
extern ErrorType error[11];

/* Define a structure for register types */
typedef struct RegsType {
    char *reg_name;
    int reg_num;
} RegsType;

/* Declare an external array of register types */
extern RegsType regs[8];

/* Define a structure for label nodes */
typedef struct LabelNode {
    char label[50];
    int address;
    struct LabelNode *next;
} LabelNode;

/* Define a structure for memory words */
typedef struct mem_word {
    char *name;
    int value;
} mem_word;

/* Declare function prototypes */
int is_valid_label(char *label);
int *method_OpDivider(char *operands, char **first_op, char **second_op, mem_word *label_lst);
int search_data(char *operand, mem_word *label_lst);
int functions(int command, char *operands, int *curr_IC, int *curr_DC, char ***base64Chars, mem_word *label_lst, char *filename);
int convertToBase64(short decimalNumber, char *base64Chars);
FILE *openEntFile(const char *name);
void writeToEntFile(const char *filename, const char *line);
void closeEntFile(const char *filename);
FILE *openExtFile(const char *name);
void writeToExtFile(const char *filename, const char *line);
void closeExtFile(const char *filename);
int *data_op_divider(char *operands);
int *string_op_divider(char *operands);
void delAllFiles(const char *fileName);
void delextFiles(const char *name);
void delentFiles(const char *name);

#endif
