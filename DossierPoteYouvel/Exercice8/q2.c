#include "../Exercice4/exfour.h"

void *resolve_addressing(CPU *cpu, const char *operand)
{
    void *result;

    if ((result = segment_override_addressing(cpu, operand)))
        return result;
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
