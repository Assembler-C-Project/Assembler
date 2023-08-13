#ifndef STATES_H
#define STATES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum opcode
{
    MOV,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    STOP
};

enum directivecode
{
    DATA,
    STRING,
    ENTRY,
    EXTERN
};

#endif
