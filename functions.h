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

int *method_OpDivider(char *operands, char **first_op, char **second_op);
int search_data(char *operand);
void functions(int command, char *operands);

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
