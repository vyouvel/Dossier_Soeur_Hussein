#include "../Exercice4/exfour.h"

void *segment_override_addressing(CPU *cpu, const char *operand)
{
    if (!matches("^\\[[A-Z]{2}:[A-Z]{2}\\]$", operand))
        return NULL;

    char segment[3], reg[3];
    sscanf(operand, "[%2[^:]:%2[^]]]", segment, reg);
    Segment *seg = hashmap_get(cpu->memory_handler->allocated, segment);
    int *reg_val = hashmap_get(cpu->context, reg);

    if (!seg || !reg_val || *reg_val >= seg->size)
        return NULL;
    return cpu->memory_handler->memory[seg->start + *reg_val];
}
