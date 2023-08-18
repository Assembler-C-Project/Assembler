/*functions.c
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: define various utility functions and data structures used in an assembly language decoder program, including error messages, register mappings, operand caching methods, binary conversion, file handling for entry and external files, data and string operand division, and deletion of specific files related to assembly output.*/
#include "functions.h"
/*caching_methods_values=[ 0:first_operand_meth   1:first_operand_value,
                           2:second_operand_meth  3:second_operand_value 4:number of operands]*/

/* Error messages for different issues */
ErrorType error[] = {{ERR_2_OPS, "Expected 2 operands\n"},
                     {ERR_1_OP, "Expected 1 valid operand\n"},
                     {ERR_0_OP, "Command doesn't take operands\n"},
                     {ERR_DEST_TYPE, "Destination operand type error\n"},
                     {ERR_SRC_TYPE, "Source operand type error\n"},
                     {ERR_INV_LABEL, "Invalid label name\n"},
                     {ERR_INV_CMD, "Command/Instruction not found!\n"},
                     {ERR_INV_ENT, "Invalid entry name"},
                     {ERR_VAR_NF, "Variable not found"},
                     {ERR_INV_REG, "Invalid register number"},
                     {ERR_INV_NUM, "The decimalNumber is not a 12 bits number.\n"}

};

/* Register names and their corresponding numbers */
RegsType regs[] = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7}

};

int functions(int command, char *operands, int *curr_IC, int *curr_DC, char ***base64Chars, mem_word *label_lst, char *filename)
{
    int IC;
    int DC;
    int *caching_methods_values;
    int err_msg;
    int err_num;
    int j, i;
    char *first_op;
    char *second_op;
    int *binaries;
    int f_binaryint, s_binaryint, t_binaryint;
    int first_meth, second_meth, first_value, second_value, num_of_ops;
    char ext_line[20], ent_line[20];
    /* Initializing variables */
    binaries = malloc(3 * sizeof(int));
    binaries[0] = binaries[1] = binaries[2] = binaries[3] = END_OF_BIN;
    f_binaryint = s_binaryint = t_binaryint = END_OF_BIN;
    err_num = 0;
    err_msg = -1;
    IC = 0;
    DC = 0;
    if (command < 16)
    {
        /* Divide operands into caching methods */
        caching_methods_values = method_OpDivider(operands, &first_op, &second_op, label_lst);
        first_meth = caching_methods_values[0];
        first_value = caching_methods_values[1];
        second_meth = caching_methods_values[2];
        second_value = caching_methods_values[3];
        num_of_ops = caching_methods_values[4];
        err_msg = caching_methods_values[5];
        if (err_msg != -1)
        {
            err_num++;
        }
        /* Check for various errors based on the command and operands */
        if (!err_num && num_of_ops != 2 && ((command >= MOV && command <= SUB) || command == LEA))
        {
            err_msg = ERR_2_OPS;
            err_num++;
        }
        if (!err_num && num_of_ops != 1 && ((command >= INC && command <= JSR) || command == NOT || command == CLR))
        {
            err_msg = ERR_1_OP;
            err_num++;
        }
        if (!err_num && num_of_ops != 0 && (command == STOP || command == RTS))

        {
            err_msg = ERR_0_OP;
            err_num++;
        }

        /* Check operand types and handle errors */
        if (!err_num && (second_meth == 1) && (command != CMP && command != PRN && command != STOP && command != RTS))
        {
            err_msg = ERR_DEST_TYPE;
            err_num++;
        }
        if (!err_num && first_meth != 3 && command == LEA)
        {
            err_msg = ERR_SRC_TYPE;
            err_num++;
        }

        /* If no errors, proceed to create binaries */
        if (!err_num)
        {
            /* Construct the first part of the binary representation */
            f_binaryint = 0;
            f_binaryint |= (first_meth << SOURCE_OPERAND_SHIFT);
            f_binaryint |= (command << OPCODE_SHIFT);
            f_binaryint |= (second_meth << DESTINATION_OPERAND_SHIFT);

            binaries[0] = f_binaryint;
            IC++;

            /* Handle various cases for different operand combinations */
            if ((first_meth || second_meth))
            {
                s_binaryint = 0;

                if (first_meth == 5)
                {
                    s_binaryint |= (first_value << SOURCE_REG_SHIFT);
                    if (second_meth == 5)
                    {
                        s_binaryint |= (second_value << DESTINATION_REG_SHIFT);
                    }

                    else if (second_meth == 3 || second_meth == 1)
                    {
                        t_binaryint = 0;
                        t_binaryint |= (second_value << 2);
                        if (second_meth == 3)
                        {
                            t_binaryint |= 2;
                            if (!second_value)
                            {
                                t_binaryint = 1;
                            }
                        }
                        binaries[2] = t_binaryint;
                        IC++;
                    }
                    binaries[1] = s_binaryint;
                    IC++;
                }
                else if (first_meth == 3 || first_meth == 1)
                {
                    s_binaryint |= (first_value << 2);
                    if (first_meth == 3)
                    {
                        s_binaryint |= 2;
                        if (!first_value)
                        {
                            s_binaryint = 1;
                        }
                    }
                    if (second_meth == 5)
                    {
                        t_binaryint = 0;
                        t_binaryint |= (second_value << DESTINATION_REG_SHIFT);
                        binaries[2] = t_binaryint;
                        IC++;
                    }
                    else if (second_meth == 3 || second_meth == 1)
                    {
                        t_binaryint = 0;
                        t_binaryint |= (second_value << 2);
                        if (second_meth == 3)
                        {
                            t_binaryint |= 2;
                            if (!second_value)
                            {
                                t_binaryint = 1;
                            }
                        }
                        binaries[2] = t_binaryint;
                        IC++;
                    }
                    binaries[1] = s_binaryint;
                    IC++;
                }
                if (!first_op)
                {
                    if (second_meth == 5)
                    {
                        s_binaryint |= (second_value << DESTINATION_REG_SHIFT);
                    }
                    else if (second_meth == 3 || second_meth == 1)
                    {
                        s_binaryint |= (second_value << 2);
                        if (second_meth == 3)
                        {
                            s_binaryint |= 2;
                            if (!second_value)
                            {
                                s_binaryint = 1;
                            }
                        }
                    }
                    binaries[1] = s_binaryint;
                    IC++;
                }
            }
            /* Handle cases involving direct mapping */
            if (first_meth == DIRECT_MAPPING || second_meth == DIRECT_MAPPING)
            {
                if (first_value == 0 || second_value == 0)
                {
                    if (first_value == 0 && first_meth == DIRECT_MAPPING)
                    {
                        sprintf(ext_line, "%s %d", first_op, 101 + *curr_DC + DC + *curr_IC + DC);
                    }
                    if (second_value == 0 && second_meth == DIRECT_MAPPING)
                    {
                        sprintf(ext_line, "%s %d", second_op, 100 + num_of_ops + *curr_DC + DC + *curr_IC + DC);
                    }
                    writeToExtFile(filename, ext_line);
                }
                if (first_value == -1 || second_value == -1)
                {
                    err_msg = ERR_VAR_NF;
                }
            }
        }
    }
    /* Handle non-instruction commands like data, string, entry, and extern */
    else
    {
        if (command == IS_DATA)
        {
            if (data_op_divider(operands) == NULL)
            {
                err_msg = ERR_1_OP;
            }
            else
            {
                binaries = data_op_divider(operands);
            }
        }
        else if (command == IS_STRING)
        {
            if (string_op_divider(operands) == NULL)
            {

                err_msg = ERR_SRC_TYPE;
            }
            else
            {
                binaries = string_op_divider(operands);
                DC++;
            }
        }
        else if (command == IS_ENTRY)
        {
            /* Check if doublicates with extern*/
            j = 0;
            while (label_lst[j].value != '\0')
            {
                if (!strcmp(operands, label_lst[j].name) && label_lst[j].value != -1)
                {
                    sprintf(ent_line, "%s %d", label_lst[j].name, label_lst[j].value);
                    writeToEntFile(filename, ent_line);
                    break;
                }
                j++;
            }
            if (j != 0 && label_lst[j].value == '\0')
            {
                err_msg = ERR_INV_ENT;
            }
        }
        else if (command == IS_EXTERN)
        {
            j = 0;
            while (label_lst[j].value != '\0')
            {
                if (!strcmp(operands, label_lst[j].name) && label_lst[j].value != -1)
                {
                    err_msg = ERR_INV_LABEL;
                }
                j++;
            }
        }

        j = 0;
        while (binaries[j] != END_OF_BIN)
        {
            j++;
        }
        DC = j;
    }
    j = *curr_IC + *curr_DC;
    *curr_IC += IC;
    *curr_DC += DC;
    *base64Chars = (char **)realloc(*base64Chars, (*curr_IC + *curr_DC + 1) * sizeof(char *));
    i = 0;
    while (binaries[i] != END_OF_BIN)
    {
        (*base64Chars)[j] = (char *)malloc(3 * sizeof(char));
        err_msg = convertToBase64(binaries[i], (*base64Chars)[j]);
        j++;
        i++;
    }
    return err_msg;
}

/* Caching method and operand divider function*/
int *method_OpDivider(char *operands, char **first_op, char **second_op, mem_word *label_lst)
{
    int *result;
    char *err;
    char *rest;
    int first_meth;
    int second_meth;
    int i;
    int first_value;
    int second_value;
    int num_of_ops;
    int err_msg;
    /* Allocate memory to store the result */
    result = malloc(sizeof(int) * 6);
    num_of_ops = 0;
    first_meth = second_meth = first_value = second_value = END_OF_BIN;
    err_msg = -1;
    /* Divide the operands into first and second operands */
    *first_op = strtok(operands, ",");
    rest = strtok(NULL, " ");
    if (rest == NULL)
    {
        rest = *first_op;
        *first_op = NULL;
    }
    *second_op = strtok(rest, " ");

    /* Determine the caching methods and values for operands */
    first_meth = 0;
    second_meth = 0;

    if (*first_op)
    {
        num_of_ops++;
        first_value = strtol(*first_op, &err, 10);

        /* Check if the operand is a direct register */
        if (!strncmp((*first_op), "@r", 2))
        {
            first_meth = DIRECT_REG_MAPPING;
            i = 0;
            while (i < NUM_OF_REGS)
            {
                if (!strcmp((*first_op + 1), regs[i].reg_name))
                {
                    first_value = regs[i].reg_num;
                    break;
                }
                i++;
            }
            if (i > NUM_OF_REGS - 1)
            {
                err_msg = ERR_INV_REG;
            }
        }
        /* Check if the operand is an immediate value */
        else if (!*err)
        {
            first_meth = IMMEDIATE_MAPPING;
        }
        /* Otherwise, assume it's a direct mapping and search for the value */
        else
        {
            first_meth = DIRECT_MAPPING;
            first_value = search_data(*first_op, label_lst);
        }
    }

    /* Similar checks and assignments for the second operand */
    if (*second_op)
    {
        num_of_ops++;
        second_value = strtol(*second_op, &err, 10);

        if (!strncmp((*second_op), "@r", 2))
        {

            second_meth = DIRECT_REG_MAPPING;
            for (i = 0; i < NUM_OF_REGS; i++)
            {
                if (!strcmp((*second_op + 1), regs[i].reg_name))
                {
                    second_value = regs[i].reg_num;
                    break;
                }
            }
            if (i > NUM_OF_REGS - 1)
            {
                err_msg = ERR_INV_REG;
            }
        }
        else if (!*err)
        {
            second_meth = IMMEDIATE_MAPPING;
        }
        else
        {
            second_meth = DIRECT_MAPPING;
            second_value = search_data(*second_op, label_lst);
        }
    }
    /* Store the results in the 'result' array and return it */
    result[0] = first_meth;
    result[1] = first_value;
    result[2] = second_meth;
    result[3] = second_value;
    result[4] = num_of_ops;
    result[5] = err_msg;

    return result;
}
int *data_op_divider(char *operands)
{
    int *val_ptr;
    int i;
    char *token, *err;
    char curr_ops[100];
    err = NULL;
    /* Allocate memory for the integer values array */
    val_ptr = (int *)malloc(1 * sizeof(int));
    strcpy(curr_ops, operands);
    i = 0;

    /* Tokenize the input string and extract integer values */
    token = strtok(curr_ops, ",");
    while (token != NULL)
    {
        /* Reallocate memory to store the extracted value */
        val_ptr = realloc(val_ptr, (i + 2) * sizeof(int));

        /* Convert token to integer and store in the array */
        val_ptr[i] = strtol(token, &err, 10);

        /* Check for parsing error */
        if (!*err)
        {
            i++;
        }
        else
        {
            /* Free memory and return NULL if parsing error occurs */
            free(val_ptr);
            return NULL;
        }

        token = strtok(NULL, ",");
    }

    /* Mark the end of the integer values array */
    val_ptr[i] = -3000;

    return val_ptr;
}

int *string_op_divider(char *operands)
{
    int *val_ptr;
    int i, size;
    size = strlen(operands);

    /* Check if the string is enclosed in double quotes */
    if (operands[0] == '"' && operands[size - 1] == '"')
    {
        /* Allocate memory for the integer values array */
        val_ptr = (int *)malloc((size + 1) * sizeof(int));

        i = 0;

        /* Extract character values from the string and store them as integers */
        while (i < size - 2)
        {
            val_ptr[i] = (int)operands[i + 1];
            i++;
        }

        /* Mark the end of the integer values array */
        val_ptr[i] = '\0';
        val_ptr[i + 1] = END_OF_BIN;

        return val_ptr;
    }

    /* Return NULL if the input string is not a valid enclosed string */
    return NULL;
}

int search_data(char *operand, mem_word *label_lst)
{
    int i = 0;

    /* Iterate through the label list to find the specified operand */
    while (label_lst[i].value != '\0')
    {
        /* Check if the operand matches the current label */
        if (!strcmp(label_lst[i].name, operand))
        {
            /* Check if the label value indicates an undefined variable */
            if (label_lst[i].value == -1)
            {
                /* Return 0 to indicate an undefined variable */
                return 0;
            }
            else
            {
                /* Return the value associated with the label */
                return label_lst[i].value;
            }
        }
        i++;
    }

    /* Return -1 if the operand is not found in the label list */
    return -1;
}

int convertToBase64(short decimalNumber, char *base64Chars)
{
    int err_msg;
    char base64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    err_msg = -1;
    /* Make sure the decimalNumber is 12 bits.*/
    if (decimalNumber < -2048 || decimalNumber > 4095)
    {
        err_msg = ERR_INV_NUM;
    }

    /* Extract the first and second 6 bits and convert to corresponding base64 characters. */
    base64Chars[0] = base64Map[(decimalNumber & 0xFC0) >> 6];
    base64Chars[1] = base64Map[decimalNumber & 0x3F];
    base64Chars[2] = '\0';
    return err_msg;
}

FILE *openEntFile(const char *name)
{
    char filename[50];
    FILE *file;

    /* Create the filename for the .ent file by appending ".ent" to the input name */
    strcpy(filename, name);
    strcat(filename, ".ent");

    /* Try to open the file in read mode to check if it exists */
    file = fopen(filename, "r");

    if (file)
    {
        /* If the file exists, close it */
        fclose(file);

        /* Reopen the file in append mode to add content */
        file = fopen(filename, "a");
    }
    else
    {
        /* If the file doesn't exist, create it by opening it in write mode */
        file = fopen(filename, "w");
    }

    /* Return the file pointer, either for appending or creating the file */
    return file;
}

void writeToEntFile(const char *filename, const char *line)
{
    FILE *file = openEntFile(filename);

    if (file)
    {
        /* Write the provided line to the file followed by a newline character */
        fprintf(file, "%s\n", line);
        fclose(file); /* Close the file after writing */
    }
    else
    {
        printf("Failed to open the file.\n"); /* Print an error message if file couldn't be opened */
    }
}

void closeEntFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
        fclose(file); /* Close the file if it was successfully opened */
    }
    /* If the file couldn't be opened, it might not need to be closed, so no error message is provided */
}

FILE *openExtFile(const char *name)
{
    char filename[50];
    FILE *file;
    strcpy(filename, name);
    strcat(filename, ".ext");
    file = fopen(filename, "r");
    if (file)
    {
        /* If the file exists, close it and reopen it in append mode */
        fclose(file);
        file = fopen(filename, "a");
    }
    else
    {
        /* If the file doesn't exist, open it in write mode to create it */
        file = fopen(filename, "w");
    }

    return file;
}

void writeToExtFile(const char *filename, const char *line)
{
    FILE *file = openExtFile(filename);

    if (file)
    {
        /* Write the provided line to the file followed by a newline character */
        fprintf(file, "%s\n", line);
        fclose(file); /* Close the file after writing */
    }
    else
    {
        printf("Failed to open the file.\n"); /* Print an error message if file couldn't be opened */
    }
}

void closeExtFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
        fclose(file); /* Close the file if it was successfully opened */
    }
    /* If the file couldn't be opened, it might not need to be closed, so no error message is provided */
}

int is_valid_label(char *label)
{
    int i;
    /* Check if the label is empty */
    if (label[0] == '\0')
    {
        return 0;
    }

    /*Check if the first character is a valid start for a label*/
    if (!isalpha(label[0]) && label[0] != '_')
    {
        return 0;
    }

    /* Check the rest of the characters*/
    for (i = 1; i < strlen(label); i++)
    {
        if (!isalnum(label[i]) && label[i] != '_')
        {
            return 0;
        }
    }

    return 1;
}
void delAllFiles(const char *name)
{
    char fileName[50];
    FILE *amFile;
    FILE *obFile;
    FILE *entFile;
    FILE *extFile;
    char am[50], ob[50], ent[50], ext[50];

    strcpy(fileName, name);

    strcpy(am, fileName);
    strcat(am, ".am");

    strcpy(ob, fileName);
    strcat(ob, ".ob");

    strcpy(ent, fileName);
    strcat(ent, ".ent");

    strcpy(ext, fileName);
    strcat(ext, ".ext");

    if ((amFile = fopen(am, "r")) != NULL)
    {
        fclose(amFile); /* Close the file if it was successfully opened */
        remove(am);     /* Delete the file */
    }
    if ((obFile = fopen(ob, "r")) != NULL)
    {
        fclose(obFile); /* Close the file if it was successfully opened */
        remove(ob);     /* Delete the file */
    }
    if ((entFile = fopen(ent, "r")) != NULL)
    {
        fclose(entFile); /* Close the file if it was successfully opened */
        remove(ent);     /* Delete the file */
    }
    if ((extFile = fopen(ext, "r")) != NULL)
    {
        fclose(extFile); /* Close the file if it was successfully opened */
        remove(ext);     /* Delete the file */
    }
}

void delextFiles(const char *name)
{
    char fileName[50];

    FILE *extFile;
    char ext[50];

    strcpy(fileName, name);

    strcpy(ext, fileName);
    strcat(ext, ".ext");

    if ((extFile = fopen(ext, "r")) != NULL)
    {
        fclose(extFile); /* Close the file if it was successfully opened */
        remove(ext);     /* Delete the file */
    }
}

void delentFiles(const char *name)
{
    char fileName[50];

    FILE *entFile;
    char ent[50];

    strcpy(fileName, name);

    strcpy(ent, fileName);
    strcat(ent, ".ent");

    if ((entFile = fopen(ent, "r")) != NULL)
    {
        fclose(entFile); /* Close the file if it was successfully opened */
        remove(ent);     /* Delete the file */
    }
}
