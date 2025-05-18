#include "../Exercice4/exfour.h"

// Résout le type d’adressage automatiquement
void *resolve_addressing(CPU *cpu, const char *operand)
{
    void *result;

    if ((result = immediate_addressing(cpu, operand)))
        return result;
    if ((result = register_addressing(cpu, operand)))
        return result;
    if ((result = memory_direct_addressing(cpu, operand)))
        return result;
    if ((result = register_indirect_addressing(cpu, operand)))
        return result;
    return NULL;
}
