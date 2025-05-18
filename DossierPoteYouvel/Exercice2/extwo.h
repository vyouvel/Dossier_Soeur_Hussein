#ifndef EXTWO_H
#define EXTWO_H

#include "../Exercice1/exone.h"

/*
 * Représente un segment mémoire libre ou alloué.
 * Utilisé pour gérer les zones libres avec une liste chaînée.
 */
typedef struct segment
{
    int start;
    int size;
    struct segment *next;
} Segment;

/*
 * Représente le gestionnaire de mémoire global.
 * Contient la mémoire réelle, la liste des zones libres, et les segments alloués.
 */
typedef struct memoryHandler
{
    void **memory;
    int total_size;
    Segment *free_list;
    HashMap *allocated;
} MemoryHandler;

MemoryHandler *memory_init(int);
Segment *find_free_segment(MemoryHandler *, int, int, Segment **);
int create_segment(MemoryHandler *, const char *, int, int);
int remove_segment(MemoryHandler *, const char *);
#endif
