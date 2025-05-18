#include "exone.h"

/*
 * Cherche la valeur associée à une clé.
 * Retourne NULL si la clé n’existe pas ou a été supprimée.
 */
void *hashmap_get(HashMap *map, const char *key)
{
    unsigned long index = simple_hash(key);

    for (int i = 0; i < map->size; i++)
    {
        int probe_idx = (index + i) % map->size;
        HashEntry *entry = &map->table[probe_idx];

        if (entry->key == NULL && entry->value != TOMBSTONE)
            return NULL;
        if (entry->key != NULL && strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
    }

    return NULL;
}
