#include "../Exercice4/exfour.h"

// Adressage indirect : [AX] = contenu de l'adresse pointée par un registre
void *register_indirect_addressing(CPU *cpu, const char *operand)
{
    if (!matches("^\\[(AX|BX|CX|DX)\\]$", operand))
        return NULL;
    char reg[3] = {operand[1], operand[2], '\0'};
    int *reg_val = hashmap_get(cpu->context, reg);

    if (!reg_val)
        return NULL;
    return cpu->memory_handler->memory[*reg_val];
}
