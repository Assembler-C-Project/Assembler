#include "functions.c"

void decoder(char line[]);

struct
{
    char *name;
    int value;
} cmds[] = {
    {"mov", MOV}, {"cmp", CMP}, {"add", ADD}, {"sub", SUB}, {"not", NOT}, {"clr", CLR}, {"lea", LEA}, {"inc", INC}, {"dec", DEC}, {"jmp", JMP}, {"bne", BNE}, {"red", RED}, {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, {"stop", STOP}};
