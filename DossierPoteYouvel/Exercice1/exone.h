#ifndef EXONE_H
#define EXONE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Représente une entrée dans la table de hachage : une paire clé-valeur
typedef struct hashentry
{
    char *key;
    void *value;
} HashEntry;

// Représente la table de hachage entière
typedef struct hashmap
{
    int size;
    HashEntry *table;
} HashMap;

// Taille fixe de la table de hachage (choisie arbitrairement comme 128)
#define TABLE_SIZE 128

// Valeur spéciale utilisée pour marquer une case supprimée (tombstone)
#define TOMBSTONE ((void *)-1)

HashMap *hashmap_create();
unsigned long simple_hash(const char *);
int hashmap_insert(HashMap *, const char *, void *);
void *hashmap_get(HashMap *, const char *);
int hashmap_remove(HashMap *, const char *);
void hashmap_destroy(HashMap *);

#endif
