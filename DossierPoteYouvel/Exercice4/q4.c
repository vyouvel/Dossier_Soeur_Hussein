#include "exfour.h"

// Charge une valeur depuis un segment et une position donnée
void *load(MemoryHandler *handler, const char *segment_name, int pos)
{
    Segment *segment = hashmap_get(handler->allocated, segment_name);

    if (!segment || pos >= segment->size)
        return NULL;
    return handler->memory[segment->start + pos];
}
