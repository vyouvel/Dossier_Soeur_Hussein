#include "../Exercice4/exfour.h"

int free_es_segment(CPU *cpu)
{
    int *es = hashmap_get(cpu->context, "ES");

    if (!es || *es == -1)
        return -1;

    Segment *seg = hashmap_get(cpu->memory_handler->allocated, "ES");

    if (!seg)
        return -1;
    for (int i = 0; i < seg->size; i++)
    {
        void *val = load(cpu->memory_handler, "ES", i);
        if (val)
            free(val);
    }
    remove_segment(cpu->memory_handler, "ES");
    *es = -1;
    return 0;
}
