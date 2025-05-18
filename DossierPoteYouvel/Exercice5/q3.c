#include "../Exercice4/exfour.h"

// Adressage registre : AX, BX, CX, DX
void *register_addressing(CPU *cpu, const char *operand)
{
    if (!matches("^(AX|BX|CX|DX)$", operand))
        return NULL;
    return hashmap_get(cpu->context, operand);
}
