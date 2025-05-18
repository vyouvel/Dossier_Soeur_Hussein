#include "exone.h"

/*
 * Libère toute la mémoire allouée par la table.
 * Ne libère PAS les valeurs (void*) car elles peuvent être gérées ailleurs.
 */
void hashmap_destroy(HashMap *map)
{
    if (!map)
    {
        return;
    }
    for (int i = 0; i < map->size; i++)
    {
        if (map->table[i].key != NULL)
        {
            free(map->table[i].key);
        }
    }
    free(map->table);
    free(map);
    return;
}
