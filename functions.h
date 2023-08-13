#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "states.h"

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
enum error_code
{
    ERR_2_OPS,
    ERR_1_OP,
    ERR_0_OP,
    ERR_DEST_TYPE,
    ERR_SRC_TYPE,
    ERR_INV_LABEL,
    ERR_INV_CMD
};

typedef struct ErrorType
{
    int num;
    char *message;
} ErrorType;

extern ErrorType error[7];

typedef struct RegsType
{
    char *reg_name;
    int reg_num;
} RegsType;

extern RegsType regs[8];

typedef struct LabelNode
{
    char label[50];
    int address;
    struct LabelNode *next;
} LabelNode;
typedef struct mem_word
{
    char *name;
    int value;
} mem_word;
int is_valid_label(char *label);
int *method_OpDivider(char *operands, char **first_op, char **second_op,mem_word *label_lst);
int search_data(char *operand,mem_word *label_lst);
int functions(int command, char *operands, int *curr_IC, int *curr_DC, char ***base64Chars, mem_word *label_lst,char *filename);
void convertToBase64(short decimalNumber, char *base64Chars);
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

#endif
