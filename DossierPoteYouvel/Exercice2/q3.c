#include "extwo.h"

/*
 * Alloue un nouveau segment nommé (ex: "DS", "CS").
 * Modifie la liste des zones libres (free_list) en conséquence.
 */
int create_segment(MemoryHandler *handler, const char *name, int start, int size)
{
    Segment *prev = NULL;
    Segment *free_segment = find_free_segment(handler, start, size, &prev);

    if (!free_segment)
        return 0;

    // Alloue un nouveau segment alloué et l'ajoute à la hashmap
    Segment *new_segment = (Segment *)malloc(sizeof(Segment));

    new_segment->start = start;
    new_segment->size = size;
    new_segment->next = NULL;
    hashmap_insert(handler->allocated, name, new_segment);
    // Ajustement de la free_list selon la position de l'allocation
    if (free_segment->start == start && (start + size) == (free_segment->start + free_segment->size))
    {
        // Cas 1 : le bloc libre est exactement la taille qu'on veut -> on le supprime
        if (prev)
            prev->next = free_segment->next;
        else
            handler->free_list = free_segment->next;
    }
    else if (free_segment->start == start)
    {
        // Cas 2 : on alloue au début du bloc libre
        free_segment->start = (start + size);
        free_segment->size = (free_segment->start + free_segment->size) - (start + size);
    }
    else if ((free_segment->start + free_segment->size) == (start + size))
    {
        // Cas 3 : on alloue à la fin du bloc libre
        free_segment->size = start - free_segment->start;
    }
    else
    {
        // Cas 4 : au milieu, on doit couper le bloc libre en deux
        Segment *free_segment_ = (Segment *)malloc(sizeof(Segment));

        free_segment_->start = start + size;
        free_segment_->size = (free_segment->start + free_segment->size) - (start + size);
        free_segment_->next = free_segment->next;
        free_segment->size = start - free_segment->start;
        free_segment->next = free_segment_;
    }
    return 1;
}
