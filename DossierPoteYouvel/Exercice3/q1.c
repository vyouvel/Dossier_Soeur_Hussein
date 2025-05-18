#include "exthree.h"

/*
 * Parse une ligne de la section .DATA (ex : x DW 10,20,30)
 * Et :
 * - stocke l'adresse de la variable dans memory_locations
 * - compte combien d'espaces mémoire sont nécessaires
 */
Instruction *parse_data_instruction(const char *line, HashMap *memory_locations, int *current_address)
{
    Instruction *instructions = (Instruction *)malloc(sizeof(Instruction));

    // Extraction des 3 parties : nom, type (DB/DW), valeurs
    instructions->mnemonic = strtok(strdup(line), " ");
    instructions->operand1 = strtok(NULL, " ");
    instructions->operand2 = strtok(NULL, " ");
    int size = 1;

    // Si plusieurs valeurs (séparées par des virgules), on les compt
    if (instructions->operand2 && strchr(instructions->operand2, ','))
    {
        size = 1;
        for (char *p = instructions->operand2; *p; p++)
        {
            if (*p == ',')
                size++;
        }
    }
    // On associe la variable à l’adresse actuelle dans la table
    hashmap_insert(memory_locations, instructions->mnemonic, (void *)(long)(*current_address));
    // On réserve la place mémoire
    *current_address += size;
    return instructions;
}