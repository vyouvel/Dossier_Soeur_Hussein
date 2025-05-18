#include "exfour.h"

/**
 * Initialise un CPU avec :
 * - sa mémoire de taille `memory_size`
 * - ses registres internes : AX, BX, CX, DX, SP, BP, IP, ZF, SF, ES
 * - un segment pile SS de 128 cases à partir de l'adresse 100
 */
CPU *cpu_init(int memory_size)
{
    // Alloue dynamiquement la structure CPU
    CPU *cpu = (CPU *)malloc(sizeof(CPU));

    // Initialise la mémoire globale
    cpu->memory_handler = memory_init(memory_size);
    // Initialise les registres et les constantes
    cpu->context = hashmap_create();
    cpu->constant_pool = hashmap_create();
    // Liste des registres à initialiser
    char *registers[] = {"AX", "BX", "CX", "DX", "IP", "ZF", "SF", "SP", "BP", "ES"};

    for (int i = 0; i < 10; i++)
    {
        int *value = (int *)malloc(sizeof(int));
        // Tous les registres à 0 sauf ES qui vaut -1 (car non alloué)
        *value = (i == 9) ? -1 : 0;
        hashmap_insert(cpu->context, registers[i], value);
    }
    // Crée un segment pile (SS) de 128 cases à partir de l'adresse 100
    create_segment(cpu->memory_handler, "SS", 100, 128);
    // Récupère les registres SP et BP et les place à 127 (haut de la pile)
    int *sp = hashmap_get(cpu->context, "SP");
    int *bp = hashmap_get(cpu->context, "BP");

    *sp = 127;
    *bp = 127;
    return cpu;
}
