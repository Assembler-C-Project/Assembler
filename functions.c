#include "functions.h"
/*caching_methods_values=[ 0:first_operand_meth   1:first_operand_value,
                           2:second_operand_meth  3:second_operand_value]*/

void functions(int command, char *operands)
{
    int *caching_methods_values;
    int err_msg;
    char *first_op;
    char *second_op;
    int f_binaryint;
    int s_binaryint;
    int t_binaryint;

    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);

    printf("%d %d\n", caching_methods_values[0], caching_methods_values[2]);
    err_msg = 0;

    if ((caching_methods_values[2] == 1) && (command != CMP && command != PRN && command != STOP && command != RTS))
    {
        printf("Destination operand type error\n");
        err_msg = 1;
    }
    if ((caching_methods_values[2]) && (command == RTS || command == STOP))
    {
        printf("Unexpected destination operand\n");
        err_msg = 1;
    }

    if ((caching_methods_values[0]) && (command != MOV && command != CMP && command != ADD && command != SUB && command != LEA))
    {
        printf("Unexpected source operand\n");
        err_msg = 1;
    }
    if (caching_methods_values[0] != 3 && command == LEA)
    {
        printf("Source operand type error\n");
        err_msg = 1;
    }
    if (!caching_methods_values[2] && (command != RTS && command != STOP))
    {
        printf("Missed destination operand");
        err_msg = 1;
    }
    if (!caching_methods_values[0] && (command == MOV || command == CMP || command == ADD || command == SUB || command == LEA))
    {
        printf("Missed source operand");
        err_msg = 1;
    }
    f_binaryint = 0;
    s_binaryint = 0;
    t_binaryint = 0;

    if (!err_msg)
    {
        f_binaryint |= (caching_methods_values[0] << SOURCE_OPERAND_SHIFT);
        f_binaryint |= (command << OPCODE_SHIFT);
        f_binaryint |= (caching_methods_values[2] << DESTINATION_OPERAND_SHIFT);

        if (caching_methods_values[0] == 5)
        {
            s_binaryint |= (caching_methods_values[1] << SOURCE_REG_SHIFT);
            if (caching_methods_values[2] == 5)
            {
                s_binaryint |= (caching_methods_values[3] << DESTINATION_REG_SHIFT);
            }
            else if (caching_methods_values[2] == 3)
            {
                t_binaryint |= (caching_methods_values[3] << 2);
                t_binaryint |= 2;
            }
        }
        else if (caching_methods_values[0] == 3)
        {
            s_binaryint |= (caching_methods_values[1] << 2);
            s_binaryint |= 2;
            if (caching_methods_values[2] == 5)
            {
                t_binaryint |= (caching_methods_values[3] << DESTINATION_REG_SHIFT);
            }
            else if (caching_methods_values[2] == 3)
            {
                t_binaryint |= (caching_methods_values[3] << 2);
                t_binaryint |= 2;
            }
        }
        /*need to add mapping 0,(1,3,5) and 1,(1,3,5) and (3,5),1 */
    }
    free(caching_methods_values);

    printf("the binaries are: %d %d %d\n", f_binaryint, s_binaryint, t_binaryint);
}

/* Caching method and operand divider function*/
int *method_OpDivider(char *operands, char **first_op, char **second_op)
{
    int *result;
    char *err;
    char *rest;
    int first_meth;
    int second_meth;
    int i;
    int first_value;
    int second_value;

    result = malloc(sizeof(int) * 4);

    first_meth = second_meth = first_value = second_value = 0;

    /* Divider*/
    *first_op = strtok(operands, ",");
    rest = strtok(NULL, " ");
    if (rest == NULL)
    {
        rest = *first_op;
        *first_op = NULL;
    }

    *second_op = strtok(rest, " ");

    /*Caching Method*/
    first_meth = 0;
    second_meth = 0;
    if (*first_op)
    {

        first_value = strtol(*first_op, &err, 10);
        if (!strncmp((*first_op), "@r", 2))
        {

            first_meth = DIRECT_REG_MAPPING;
            for (i = 0; i < NUM_OF_REGS; i++)
            {
                if (!strncmp((*first_op + 1), regs[i].reg_name, 2))
                {
                    first_value = regs[i].reg_num;
                    break;
                }
            }
            if (i > NUM_OF_REGS - 1)
            {
                printf("Err: Wrong register number\n");
            }
        }

        else if (!*err)
        {
            first_meth = IMMEDIATE_MAPPING;
        }
        else
        {
            first_meth = DIRECT_MAPPING;
            first_value = search_data(*first_op);
        }
    }

    if (*second_op)
    {

        second_value = strtol(*second_op, &err, 10);
        if (!strncmp((*second_op), "@r", 2))
        {

            second_meth = DIRECT_REG_MAPPING;
            for (i = 0; i < NUM_OF_REGS; i++)
            {
                if (!strncmp((*second_op + 1), regs[i].reg_name, 2))
                {
                    second_value = regs[i].reg_num;
                    break;
                }
            }
            if (i > NUM_OF_REGS - 1)
            {
                printf("Err: Wrong register number\n");
            }
        }

        else if (!*err)
        {
            second_meth = IMMEDIATE_MAPPING;
        }
        else
        {
            second_meth = DIRECT_MAPPING;
            second_value = search_data(*second_op);
        }
    }

    result[0] = first_meth;
    result[1] = first_value;
    result[2] = second_meth;
    result[3] = second_value;

    return result;
}
int search_data(char *operand)
{
    return 125;
    /*-returns a value from the data sheet*/
}
