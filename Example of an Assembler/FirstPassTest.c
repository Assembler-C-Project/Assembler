#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LabelNode {
    char label[50];
    int address;
    struct LabelNode *next;
}LabelNode;

void insertLabel(struct LabelNode **head, const char *label, int address) {
    struct LabelNode *newNode = (struct LabelNode *)malloc(sizeof(struct LabelNode));
    strcpy(newNode->label, label);
    newNode->address = address;
    newNode->next = *head;
    *head = newNode;
}


void runFirsPass(FILE *file, LabelNode *labels) 
{
    char line[100], label[50], *directive, *str, *data, line_copy[100], *command;
    int currentAddress, result, strLength, num, count, i;
    struct LabelNode *temp;
    const char *commands[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec",
                              "jmp", "bne", "red", "prn", "jsr", "stop", "rts"};
    const int commandIncrements[] = {3, 3, 3, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1};


    file = fopen("source_file.am", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    currentAddress = 100;
    labels = NULL;

    while (fgets(line, sizeof(line), file)) 
    {
        result = sscanf(line, "%49s", label);
        strcpy(line_copy, line);
        directive = strtok(line_copy, " \t\n:");
        if (result == 1 && label[strlen(label) - 1] == ':') 
        {
            command = strtok(NULL, " ");
            label[strlen(label) - 1] = '\0';
            insertLabel(&labels, label, currentAddress);
        }
        else
        {
            command = directive;
        }
        if (directive) 
        {
            if (directive[0] != '.') 
            {
                if (strstr(line, ".string")) 
                {
                    str = strtok(NULL, "\"");
                    if (str) 
                    {
                        strLength = strlen(str);
                        currentAddress += strLength + 1;
                    }
                } 
                else if (strstr(line, ".data")) 
                {
                    data = strchr(line, ' ');
                    strtok(data, " ");
                    data = strtok(NULL, " ");
                    if (data) 
                    {
                        while (1) 
                        {
                            count = sscanf(data, "%d", &num);
                            if (count == 1) 
                            {
                                currentAddress += 1;
                                while (*data != ',' && *data != '\0') 
                                {
                                    data++;
                                }
                                if (*data == ',') 
                                {
                                    data++;
                                } 
                                else 
                                {
                                    break;
                                }
                            } 
                            else 
                            {
                                break;
                            }
                        }
                    }
                } 
                else 
                {
                    for (i = 0; i < 16; i++) 
                    {
                        if (strcmp(command, commands[i]) == 0) 
                        {
                            currentAddress += commandIncrements[i];
                            break;
                        }
                    }
                    if(i == 16)
                    {
                        currentAddress += 1;
                    }
                }
            }
        }
    }


    /*while (labels != NULL) {
        temp = labels;
        labels = labels->next;
        free(temp);
    }*/

return 0;
}



