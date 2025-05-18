#include "extwo.h"

/*
 * Recherche dans la free_list un segment qui contient la plage [start, start+size[
 * Retourne le segment trouvé et met à jour prev (le segment précédent).
 */
Segment *find_free_segment(MemoryHandler *handler, int start, int size, Segment **prev)
{
    Segment *current = handler->free_list;

    *prev = NULL;
    while (current)
    {
        if (current->start <= start && (current->start + current->size) >= (start + size))
        {
            return current;
        }
        *prev = current;
        current = current->next;
    }
    return NULL;
}
