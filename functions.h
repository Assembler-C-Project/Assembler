#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "states.h"

#define NUM_OF_REGS 8

#define IMMEDIATE_MAPPING 1
#define DIRECT_MAPPING 3
#define DIRECT_REG_MAPPING 5

#define OPCODE_SHIFT 5
#define SOURCE_OPERAND_SHIFT 9
#define DESTINATION_OPERAND_SHIFT 2

#define SOURCE_REG_SHIFT 7
#define DESTINATION_REG_SHIFT 2

enum error_code
{
    ERR_2_OPS,
    ERR_1_OP,
    ERR_0_OP,
    ERR_DEST_TYPE,
    ERR_SRC_TYPE
};

typedef struct ErrorType
{
    int num;
    char *message;
} ErrorType;

extern ErrorType error[5];

typedef struct RegsType
{
    char *reg_name;
    int reg_num;
} RegsType;

extern RegsType regs[8];


int *method_OpDivider(char *operands, char **first_op, char **second_op);
int search_data(char *operand);
int functions(int command, char *operands);
void convertToBase64(short decimalNumber, char *base64Chars);
void convertToBinary(short decimalNumber, char *binary);

#endif