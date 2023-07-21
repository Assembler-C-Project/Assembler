#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80
#define MAX_MACRO_COUNT 100
#define MAX_MACRO_LINES 100

/* Define a structure for a macro */
typedef struct {
    char name[MAX_LINE_LENGTH];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int lineCount;
} Macro;

/* Function to replace tabs with spaces in a string */
void replaceTabsWithSpaces(char* str);
/* Function to save a macro in the macro table */
void saveMacro(FILE* file, char* macroName, Macro* macroTable[], int* macroCount);
/* Function to expand the macros in the source file */
void unfoldMacros(FILE* sourceFile, FILE* outputFile, Macro* macroTable[], int* macroCount);

