#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Interpreter.c"
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
struct
{
    int num;
    char *message;

} error[] = {{ERR_2_OPS, "Expected 2 operands\n"},
             {ERR_1_OP, "Expected 1 operand\n"},
             {ERR_0_OP, "Command doesn't take operands\n"},
             {ERR_DEST_TYPE, "Destination operand type error\n"},
             {ERR_SRC_TYPE, "Source operand type error\n"}};
int *method_OpDivider(char *operands, char **first_op, char **second_op);
int search_data(char *operand);
int functions(int command, char *operands);
void convertToBase64(short decimalNumber, char *base64Chars);
void convertToBinary(short decimalNumber, char *binary);

struct
{
    char *reg_name;
    int reg_num;
} regs[] = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7}

};
