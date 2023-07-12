#include "functions.c"

void decoder(char line[]);

struct {
    char* name;
    void (*func)(char*);
} cmds[] = {
    {"mov", &mov_func}, {"cmp", &cmp_func}, {"add", &add_func}, {"sub", &sub_func},
    {"not", &not_func}, {"clr", &clr_func}, {"lea", &lea_func}, {"inc", &inc_func},
    {"dec", &dec_func}, {"jmp", &jmp_func}, {"bne", &bne_func}, {"red", &red_func},
    {"prn", &prn_func}, {"jsr", &jsr_func}, {"rts", &rts_func}, {"stop", &stop_func}
};
 
 