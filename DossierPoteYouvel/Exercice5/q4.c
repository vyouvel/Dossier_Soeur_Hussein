#include "../Exercice4/exfour.h"

// Adressage direct : [10] = adresse mémoire absolue
void *memory_direct_addressing(CPU *cpu, const char *operand)
{
    if (!matches("^\\[[0-9]+\\]$", operand))
        return NULL;
    int addr = atoi(operand + 1);

    return cpu->memory_handler->memory[addr];
}
