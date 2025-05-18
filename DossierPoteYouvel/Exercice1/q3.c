#include "exone.h"

/*
 * Insère une clé et sa valeur associée dans la table.
 * En cas de collision, applique un "linear probing" (on cherche la prochaine case libre).
 */
int hashmap_insert(HashMap *map, const char *key, void *value)
{
    unsigned long index = simple_hash(key);
    int tombstone = -1;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int probe_idx = (index + i) % TABLE_SIZE;
        HashEntry *entry = &map->table[probe_idx];
        if (entry->key == NULL)
        {
            if (entry->value == TOMBSTONE)
            {
                if (tombstone == -1)
                    tombstone = probe_idx;
            }
            else
            {
                entry->key = strdup(key);
                entry->value = value;
                return 1;
            }
        }
        else if (strcmp(entry->key, key) == 0)
        {
            entry->value = value;
            return 1;
        }
    }
    if (tombstone != -1)
    {
        map->table[tombstone].key = strdup(key);
        map->table[tombstone].value = value;
        return 1;
    }
    return 0;
}
