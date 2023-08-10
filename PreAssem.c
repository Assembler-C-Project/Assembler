#include"PreAssem.h"

/* Function to replace tabs with spaces in a string */
void replaceTabsWithSpaces(char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\t') {
            str[i] = ' ';
        }
    }
}

/* Function to save a macro in the macro table */
void saveMacro(FILE* file, char* macroName, Macro* macroTable[], int* macroCount) {
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    (*macroCount)++;

    /* Allocate memory for new macro and save it in the macro table */
    macroTable[*macroCount - 1] = (Macro*)malloc(sizeof(Macro));
    strncpy(macroTable[*macroCount - 1]->name, macroName, MAX_LINE_LENGTH);

    /* Read the lines of the macro and save them */
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        replaceTabsWithSpaces(line);

        /* If line is "endmcro", end of macro is reached */
        if (strncmp(line, " endmcro", 8) == 0) {
            break;
        }
        strcpy(macroTable[*macroCount - 1]->lines[lineCount], line);
        lineCount++;
        macroTable[*macroCount - 1]->lineCount = lineCount;
    }
}

/* Function to expand the macros in the source file */
void unfoldMacros(FILE* sourceFile, FILE* outputFile, Macro* macroTable[], int* macroCount) 
{
    char line[MAX_LINE_LENGTH];
    char macroName[MAX_LINE_LENGTH];
    char expandedLine[MAX_LINE_LENGTH];
    int i;
    int j;

    /* Read the source file line by line */
    while (fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL) 
    {
        replaceTabsWithSpaces(line);

        /* If line starts with "mcro", save the macro */
        if (strncmp(line, " mcro", 5) == 0) 
        {
            sscanf(line, "%*s %s", macroName);
            saveMacro(sourceFile, macroName, macroTable, macroCount);
            continue;
        }

        /* Check if the line contains a macro and expand it */
        sscanf(line, "%s", macroName);
        for (i = 0; i < *macroCount; i++) 
        {
            if (strcmp(macroName, macroTable[i]->name) == 0) 
            {
                for (j = 0; j < macroTable[i]->lineCount; j++) 
                {
                    sprintf(expandedLine, "%s", macroTable[i]->lines[j]);
                    fputs(expandedLine, outputFile);
                }
                break;
            }
        }

        /* If the line did not contain a macro, write it to the output file as is */
        if (i == *macroCount) 
        {
            fputs(line, outputFile);
        }
    }
}

void RunPreAssem(FILE* sourceFile, FILE* outputFile)
{
    /* Initialize all variables needed for running the Pre Assembler*/
    Macro* macroTable[MAX_MACRO_COUNT];
    int macroCount = 0;
    int i;

    /* Initialize the macro table */
    for (i = 0; i < MAX_MACRO_COUNT; i++) {
        macroTable[i] = NULL;
    }
    /* Expand the macros in the source file and write to the output file */
    unfoldMacros(sourceFile, outputFile, macroTable, &macroCount);
    /* Close the original source file */
    fclose(sourceFile);
    /* Close the output file */
    fclose(outputFile);
    /* Free the memory allocated for the macros */
    for (i = 0; i < macroCount; i++) {
        free(macroTable[i]);
    }
}
