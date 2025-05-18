#include "../Exercice4/exfour.h"

int find_free_address_strategy(MemoryHandler *handler, int size, int strategy)
{
    Segment *segment = NULL, *current = handler->free_list;
    int addr = -1;

    if (strategy == 0)
    {
        while (current)
        {
            if (current->size >= size)
                return current->start;
            current = current->next;
        }
    }
    else
    {
        while (current)
        {
            if (current->size >= size)
            {
                if (!segment ||
                    (strategy == 1 && current->size < segment->size) ||
                    (strategy == 2 && current->size > segment->size))
                {
                    segment = current;
                }
            }
            current = current->next;
        }
        if (segment)
            return segment->start;
    }
    return -1;
}
