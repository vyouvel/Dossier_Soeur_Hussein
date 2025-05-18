#include "extwo.h"

/*
 * Initialise le gestionnaire de mémoire avec une taille donnée.
 * Crée un segment libre unique couvrant toute la mémoire.
 */
MemoryHandler *memory_init(int size)
{
    MemoryHandler *memory = (MemoryHandler *)malloc(sizeof(MemoryHandler));
    Segment *segments = (Segment *)malloc(sizeof(Segment));

    segments->start = 0;
    segments->size = size;
    segments->next = NULL;
    memory->free_list = segments;
    memory->allocated = hashmap_create();
    memory->total_size = size;
    memory->memory = (void **)malloc(sizeof(void *));
    return memory;
}
