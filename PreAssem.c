/*This is a test of push*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_MACRO_COUNT 100
#define MAX_MACRO_LINES 100

typedef struct {
    char name[MAX_LINE_LENGTH];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int lineCount;
} Macro;

Macro macroTable[MAX_MACRO_COUNT];
int macroCount = 0;

void saveMacro(FILE* file, char* macroName) {
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    macroCount++;

    strncpy(macroTable[macroCount - 1].name, macroName, MAX_LINE_LENGTH);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strncmp(line, "endmcro", 7) == 0) {
            break;
        }
        strncpy(macroTable[macroCount - 1].lines[lineCount], line, MAX_LINE_LENGTH);
        lineCount++;
        macroTable[macroCount - 1].lineCount = lineCount;
    }
}

void unfoldMacros(FILE* sourceFile, FILE* outputFile) {
    char line[MAX_LINE_LENGTH];
    int macroFlag = 0;
    char macroName[MAX_LINE_LENGTH];
    int i;

    while (fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL) {
        if (line[0] != ' ') {
            macroFlag = 0;
        }

        if (macroFlag) {
            if (strncmp(line, "endmcro", 7) == 0) {
                macroFlag = 0;
            }
            continue;
        }

        if (line[0] == ' ') {
            char macroName[MAX_LINE_LENGTH];
            sscanf(line, "%s", macroName);

            for (i = 0; i < macroCount; i++) {
                if (strcmp(macroName, macroTable[i].name) == 0) {
                    int j;
                    for (j = 0; j < macroTable[i].lineCount; j++) {
                        char expandedLine[MAX_LINE_LENGTH];
                        sprintf(expandedLine, "  %s", macroTable[i].lines[j]);
                        fputs(expandedLine, outputFile);
                    }
                    macroFlag = 1;
                    break;
                }
            }

            if (i == macroCount) {
                fputs(line, outputFile);
            }
        } else if (strncmp(line, "mcro", 4) == 0) {
            macroFlag = 1;
            sscanf(line, "%*s %s", macroName);
            saveMacro(sourceFile, macroName);
        } else {
            fputs(line, outputFile);
        }
    }
}


int main() {
    FILE* sourceFile = fopen("source_file.txt", "r");
    FILE* outputFile = fopen("output_file.txt", "w");
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(sourceFile);
        return 1;
    }

    unfoldMacros(sourceFile, outputFile);

    fclose(sourceFile);
    fclose(outputFile);

    return 0;
}
