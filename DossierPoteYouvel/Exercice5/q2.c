#include "../Exercice4/exfour.h"

// Adressage immédiat : une constante numérique (ex: MOV AX, 5)
void *immediate_addressing(CPU *cpu, const char *operand)
{
    if (!matches("^[0-9]+$", operand))
        return NULL;
    void *value = hashmap_get(cpu->constant_pool, operand);

    if (!value)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = atoi(operand);
        hashmap_insert(cpu->constant_pool, operand, num);
        return num;
    }
    return value;
}