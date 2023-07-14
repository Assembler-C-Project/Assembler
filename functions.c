#include "functions.h"
/*caching_methods_values=[ 0:first_operand_meth   1:first_operand_value,
                           2:second_operand_meth  3:second_operand_value]*/

int functions(int command, char *operands)
{
    int *caching_methods_values;
    int err_msg;
    int err_num;
    char *first_op;
    char *second_op;
    int f_binaryint;
    int s_binaryint;
    int t_binaryint;
    int first_meth, second_meth, first_value, second_value, num_of_ops;

    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    first_meth = caching_methods_values[0];
    first_value = caching_methods_values[1];
    second_meth = caching_methods_values[2];
    second_value = caching_methods_values[3];
    num_of_ops = caching_methods_values[4];

    err_num = 0;
    err_msg = -1;
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

    f_binaryint = 0;
    s_binaryint = 0;
    t_binaryint = 0;

    if (!err_num)
    {
        f_binaryint |= (first_meth << SOURCE_OPERAND_SHIFT);
        f_binaryint |= (command << OPCODE_SHIFT);
        f_binaryint |= (second_meth << DESTINATION_OPERAND_SHIFT);

        if (first_meth == 5)
        {
            s_binaryint |= (first_value << SOURCE_REG_SHIFT);
            if (second_meth == 5)
            {
                s_binaryint |= (second_value << DESTINATION_REG_SHIFT);
            }
            else if (second_meth == 3 || second_meth == 1)
            {
                t_binaryint |= (second_value << 2);
                if (second_meth == 3)
                {
                    t_binaryint |= 2;
                }
            }
        }
        else if (first_meth == 3 || first_meth == 1)
        {
            s_binaryint |= (first_value << 2);
            if (first_meth == 3)
            {
                s_binaryint |= 2;
            }
            if (second_meth == 5)
            {
                t_binaryint |= (second_value << DESTINATION_REG_SHIFT);
            }
            else if (second_meth == 3 || second_meth == 1)
            {
                t_binaryint |= (second_value << 2);
                if (second_meth == 3)
                {
                    t_binaryint |= 2;
                }
            }
        }
        if (!first_op){
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
                }
            }
        }

    }

    printf("The binaries are: %d %d %d\n", f_binaryint, s_binaryint, t_binaryint);
    return err_msg;
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
    int num_of_ops;
    result = malloc(sizeof(int) * 5);
    num_of_ops = 0;
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
        num_of_ops++;
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
        num_of_ops++;
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
    result[4] = num_of_ops;
    return result;
}
int search_data(char *operand)
{
    return 117;
    /*-returns a value from the data sheet*/
}
