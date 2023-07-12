#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Interpreter.c"
#define DIRECT_MAPPING 1
#define IMMEDIATE_MAPPING 3
#define DIRECT_REG_MAPPING 5



int* method_OpDivider(char *operands, char **first_op,char **second_op);
int search_data(char *operand);
void mov_func(char *operands) ;
void cmp_func(char *operands) ;
void add_func(char *operands) ;
void sub_func(char *operands) ;
void not_func(char *operands) ;
void clr_func(char *operands) ;
void lea_func(char *operands) ;
void inc_func(char *operands) ;
void dec_func(char *operands) ;
void jmp_func(char *operands) ;
void bne_func(char *operands) ;
void red_func(char *operands) ;
void prn_func(char *operands) ;
void jsr_func(char *operands) ;
void rts_func(char *operands) ;
void stop_func(char *operands) ;

struct {
    char *reg_name;
    int reg_num;
} regs[] = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4}
  };
 