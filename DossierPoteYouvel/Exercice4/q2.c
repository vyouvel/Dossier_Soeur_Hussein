#include "exfour.h"

/**
 * Libère proprement toutes les ressources utilisées par le CPU :
 * - registres (context)
 * - constantes (constant_pool)
 * - mémoire allouée (segments, contenu mémoire, free_list)
 */
void cpu_destroy(CPU *cpu)
{
    // Libération des registres (context)
    for (int i = 0; i < cpu->context->size; i++)
    {
        if (cpu->context->table[i].key != NULL && cpu->context->table[i].value != TOMBSTONE)
            free(cpu->context->table[i].value);
    }
    hashmap_destroy(cpu->context);
    // Libération des valeurs immédiates
    for (int i = 0; i < cpu->constant_pool->size; i++)
    {
        if (cpu->constant_pool->table[i].key != NULL && cpu->constant_pool->table[i].value != TOMBSTONE)
            free(cpu->constant_pool->table[i].value);
    }
    hashmap_destroy(cpu->constant_pool);
    // Libération de chaque case mémoire
    for (int i = 0; i < cpu->memory_handler->total_size; i++)
    {
        if (cpu->memory_handler->memory[i] != NULL)
            free(cpu->memory_handler->memory[i]);
    }
    // Libération du tableau mémoire principal
    free(cpu->memory_handler->memory);
    // Libération des segments alloués
    hashmap_destroy(cpu->memory_handler->allocated);
    // Libération de la liste chaînée des segments libres
    Segment *segment = cpu->memory_handler->free_list;

    while (segment != NULL)
    {
        Segment *tmp = segment;
        segment = segment->next;
        free(tmp);
    }
    // Libération du gestionnaire mémoire
    free(cpu->memory_handler);
    // Libération finale du CPU
    free(cpu);
}
