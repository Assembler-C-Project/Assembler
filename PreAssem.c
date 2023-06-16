#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80
#define MAX_MACRO_COUNT 100
#define MAX_MACRO_LINES 100

typedef struct {
    char name[MAX_LINE_LENGTH];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int lineCount;
} Macro;

void replaceTabsWithSpaces(char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\t') {
            str[i] = ' ';
        }
    }
}

void saveMacro(FILE* file, char* macroName, Macro* macroTable[], int* macroCount) {
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    (*macroCount)++;

    macroTable[*macroCount - 1] = (Macro*)malloc(sizeof(Macro));
    strncpy(macroTable[*macroCount - 1]->name, macroName, MAX_LINE_LENGTH);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        replaceTabsWithSpaces(line);

        if (strncmp(line, " endmcro", 8) == 0) {
            break;
        }
        strcpy(macroTable[*macroCount - 1]->lines[lineCount], line);
        lineCount++;
        macroTable[*macroCount - 1]->lineCount = lineCount;
    }
}

void unfoldMacros(FILE* sourceFile, FILE* outputFile, Macro* macroTable[], int* macroCount) {
    char line[MAX_LINE_LENGTH];
    int macroFlag = 0;
    char macroName[MAX_LINE_LENGTH];
    int i;
    int j;

    while (fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL) {
        replaceTabsWithSpaces(line);

        if (line[0] != ' ') {
            macroFlag = 0;
        }

        if (strncmp(line, " mcro", 5) == 0) {
            sscanf(line, "%*s %s", macroName);
            saveMacro(sourceFile, macroName, macroTable, macroCount);
            continue;
        }

        if (line[0] == ' ') {
            char macroName[MAX_LINE_LENGTH];
            sscanf(line, " %s", macroName);

            for (i = 0; i < *macroCount; i++) {
                if (strcmp(macroName, macroTable[i]->name) == 0) {
                    macroFlag = 1;
                    for (j = 0; j < macroTable[i]->lineCount; j++) {
                        char expandedLine[MAX_LINE_LENGTH];
                        sprintf(expandedLine, "%s", macroTable[i]->lines[j]);
                        fputs(expandedLine, outputFile);
                    }
                    break;
                }
            }

            if (i == *macroCount) {
                fputs(line, outputFile);
            }
        } else {
            fputs(line, outputFile);
        }
    }
}


int main() {
    Macro* macroTable[MAX_MACRO_COUNT];
    FILE* sourceFile = fopen("source_file.txt", "r");
    FILE* outputFile = fopen("output_file.txt", "w");
    int macroCount = 0;
    int i;

    for (i = 0; i < MAX_MACRO_COUNT; i++) {
        macroTable[i] = NULL;
    }

    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(sourceFile);
        return 1;
    }

    unfoldMacros(sourceFile, outputFile, macroTable, &macroCount);
    fclose(sourceFile);
    fclose(outputFile);

    for (i = 0; i < macroCount; i++) {
        free(macroTable[i]);
    }

    return 0;
}
