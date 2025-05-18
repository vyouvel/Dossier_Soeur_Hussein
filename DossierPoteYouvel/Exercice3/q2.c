#include "exthree.h"

/*
 * Parse une ligne de la section .CODE (ex : start: MOV AX, BX)
 * Et :
 * - extrait l'étiquette éventuelle (start:)
 * - extrait les mnémoniques et opérandes
 */
Instruction *parse_code_instruction(const char *line, HashMap *labels, int code_count)
{
    Instruction *instructions = (Instruction *)malloc(sizeof(Instruction));
    instructions->mnemonic = NULL;
    instructions->operand1 = NULL;
    instructions->operand2 = NULL;
    char *line_ = strdup(line); // copie de la ligne
    char *label = strchr(line_, ':'); // recherche d'un :

    if (label != NULL)
    {
        *label = 0; // coupe la chaîne à l'étiquette
        hashmap_insert(labels, line_, (void *)(long)code_count); // associe l’étiquette à la position
        line = label + 1; // passe au reste de l’instruction
    }
    // Extraction du mnémonique et des opérandes
    char *mnemonic = strtok(strdup(line), " ");
    char *op1 = strtok(NULL, ",");
    char *op2 = strtok(NULL, "\n");

    // Duplication si présents
    instructions->mnemonic = (mnemonic ? strdup(mnemonic) : NULL);
    instructions->operand1 = (op1 ? strdup(op1) : NULL);
    instructions->operand2 = (op2 ? strdup(op2) : NULL);

    return instructions;
}
