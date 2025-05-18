#ifndef EXTHREE_H
#define EXTHREE_H

#include "../Exercice1/exone.h"

/*
 * Représente une instruction en assembleur.
 * Elle contient :
 * - un mnémonique (ex : MOV, ADD, JMP...)
 * - un premier opérande (ex : AX, [10], ...)
 * - un second opérande (souvent source)
 */
typedef struct
{
    char *mnemonic;
    char *operand1;
    char *operand2;
} Instruction;

/*
 * Contient le résultat du parsing d'un fichier .asm.
 * On sépare les instructions .DATA et .CODE, ainsi que les métadonnées :
 * - data_instructions : tableau des instructions de déclaration de données
 * - code_instructions : tableau des instructions exécutables
 * - labels : table des étiquettes (ex : boucle:)
 * - memory_locations : table des variables avec leurs adresses en mémoire
 */
typedef struct
{
    Instruction **data_instructions;
    int data_count;
    Instruction **code_instructions;
    int code_count;
    HashMap *labels;
    HashMap *memory_locations;
} ParserResult;

Instruction *parse_data_instruction(const char *, HashMap *, int *);
Instruction *parse_code_instruction(const char *, HashMap *, int);
ParserResult *parse(const char *);
void free_parser_result(ParserResult *);
#endif