#include "../Exercice4/exfour.h"

// Récupère l'instruction suivante à exécuter
Instruction *fetch_next_instruction(CPU *cpu)
{
    int *ip = hashmap_get(cpu->context, "IP");
    Segment *seg = hashmap_get(cpu->memory_handler->allocated, "CS");

    if (!ip || !seg || *ip >= seg->size)
        return NULL;

    Instruction *instr = load(cpu->memory_handler, "CS", *ip);
    (*ip)++;
    return instr;
}
