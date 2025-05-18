#include "extwo.h"

/*
 * Libère un segment alloué, et fusionne avec les segments libres voisins si possible.
 */
int remove_segment(MemoryHandler *handler, const char *name)
{
    Segment *segment = hashmap_get(handler->allocated, name);

    if (!segment)
        return 0;
    hashmap_remove(handler->allocated, name);
    Segment *current = handler->free_list;
    Segment *prev = NULL;

    // On trouve où insérer le segment libéré dans la liste chaînée triée
    while (current != NULL && current->start < segment->start)
    {
        prev = current;
        current = current->next;
    }
    // Fusion avec le bloc précédent si adjacent
    if (prev != NULL && (prev->start + prev->size) == segment->start)
    {
        prev->size += segment->size;
        free(segment);
        segment = prev;
    }
    else // Sinon, on l'insère dans la liste
    {
        segment->next = current;
        if (prev != NULL)
            prev->next = segment;
        else
            handler->free_list = segment;
    }
    // Fusion avec le bloc suivant si adjacent
    if (current != NULL && (segment->start + segment->size) == current->size)
    {
        segment->size += current->size;
        segment->next = current->next;
        free(current);
    }
    return 1;
}
