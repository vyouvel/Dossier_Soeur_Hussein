#include "exone.h"

/*
 * Calcule un indice à partir d'une chaîne.
 * Utilise l’algorithme DJB2 (simple, rapide, efficace pour chaînes courtes).
 * Pourquoi ce choix ? Il est connu pour bien répartir les valeurs et éviter les collisions.
 */
unsigned long simple_hash(const char *str)
{
    unsigned long hash = 5381;
    int i;

    while ((i = *str++))
    {
        hash = hash * 33 + i;
    }
    return hash % TABLE_SIZE;
}
