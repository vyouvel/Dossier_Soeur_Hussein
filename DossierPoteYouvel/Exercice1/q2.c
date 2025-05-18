#include "exone.h"

/*
 * Crée une nouvelle table de hachage.
 * Alloue dynamiquement la structure et son tableau interne.
 */
HashMap *hashmap_create()
{
    HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));

    if (!hashmap)
        return NULL;
    hashmap->size = TABLE_SIZE;
    hashmap->table = (HashEntry *)malloc(sizeof(HashEntry) * TABLE_SIZE);
    if (!hashmap->table)
    {
        free(hashmap);
        return NULL;
    }
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashmap->table[i].key = NULL;
        hashmap->table[i].value = NULL;
    }
    return hashmap;
}
