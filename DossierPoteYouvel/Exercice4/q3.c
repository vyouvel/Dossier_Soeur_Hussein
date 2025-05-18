#include "exfour.h"

// Stocke une valeur à une position dans un segment nommé
void *store(MemoryHandler *handler, const char *segment_name, int pos, void *data)
{
    Segment *segment = hashmap_get(handler->allocated, segment_name);

    if (!segment || pos >= segment->size)
        return NULL;
    handler->memory[segment->start + pos] = data;
    return data;
}
