#include "../Exercice4/exfour.h"

int push_value(CPU *cpu, int value)
{
    int *sp = hashmap_get(cpu->context, "SP");
    Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");

    if (!sp || !ss || *sp < 0)
        return -1;
    int *value_ = (int *)malloc(sizeof(int));
    *value_ = value;
    store(cpu->memory_handler, "SS", *sp, value_);
    (*sp)--;
    return 0;
}
