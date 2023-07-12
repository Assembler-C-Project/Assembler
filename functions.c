#include "functions.h"
/*caching_methods_values=[ 0:first_operand_meth   1:first_operand_value,
                           2:second_operand_meth  3:second_operand_value]*/

void mov_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("mov %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void cmp_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("cmp %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/

}
void add_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("add %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void sub_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("sub %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void not_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("not %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void clr_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("clr %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void lea_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("lea %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void inc_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("inc %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void dec_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("dec %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void jmp_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("jmp %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void bne_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("bne %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void red_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("red %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void prn_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("prn %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void jsr_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("jsr %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void rts_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("rts %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}
void stop_func(char *operands)
{
    char *first_op;
    char *second_op;
    int *caching_methods_values;
    caching_methods_values = method_OpDivider(operands, &first_op, &second_op);
    /*printf("stop %s,%s :%d %d \n", first_op, second_op, caching_methods_values[0], caching_methods_values[1]);*/
}

/* Caching method and operand divider function*/
int *method_OpDivider(char *operands, char **first_op, char **second_op)
{
    char *err;
    char *rest;
    int first_meth;
    int second_meth;
    int *result;
    int i;
    int first_value;
    int second_value;
    *first_op = strtok(operands, ",");
    rest = strtok(NULL, " ");
    if (rest == NULL)
    {
        rest = *first_op;
        *first_op = NULL;
    }
    *second_op = strtok(rest, " ");

    first_value = strtol(*first_op, &err, 10);
    if (!strncmp((*first_op), "@r", 2))
    {

        first_meth = DIRECT_REG_MAPPING;
        for (i = 0; i < 5; i++)
        {
            if (!strncmp((*first_op + 1), regs[i].reg_name, 2))
            {
                first_value = regs[i].reg_num;
                break;
            }
        }
        if (i > 4)
        {
            printf("Err: Wrong register number\n");
        }
    }

    else if (err == NULL)
    {
        first_meth = IMMEDIATE_MAPPING;
    }
    else
    {
        first_meth = DIRECT_MAPPING;
        first_value = search_data(*first_op);
    }

    second_value = strtol(*second_op, &err, 10);

    if (!strncmp((*second_op), "@r", 2))
    {
        second_meth = DIRECT_REG_MAPPING;

        for (i = 0; i < 5; i++)
        {
            
            if (!strncmp((*second_op +1), regs[i].reg_name, 2))
            {
                second_value = regs[i].reg_num;
                break;
            }
        }
        if (i > 4)
        {
            printf("Err: Wrong register number\n");
        }
    }
    else if (err == NULL)
    {
        second_meth = IMMEDIATE_MAPPING;
    }
    else
    {
        second_meth = DIRECT_MAPPING;
        second_value = search_data(*second_op);
    }

    result = malloc(6 * sizeof( int));
    result[0] = first_meth;
    result[1] = first_value;
    result[2] = second_meth;
    result[3] = second_value;

    return result;
}
int search_data(char *operand){
    return 0;
/*-returns a value from the data sheet*/

}

