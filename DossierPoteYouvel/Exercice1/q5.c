#include "exone.h"

/*
 * Supprime une entrée en mettant une tombe (tombstone).
 * Cela permet de garder le bon fonctionnement du probing.
 */
int hashmap_remove(HashMap *map, const char *key)
{
    unsigned long index = simple_hash(key);

    for (int i = 0; i < map->size; i++)
    {
        int probe_idx = (index + i) % TABLE_SIZE;
        HashEntry *entry = &map->table[probe_idx];
        if (entry->key == NULL && entry->value != TOMBSTONE)
            return 0;
        if (entry->key != NULL && strcmp(entry->key, key) == 0)
        {
            free(entry->key);
            entry->key = NULL;
            entry->value = TOMBSTONE;
            return 1;
        }
    }
    return 0;
}
