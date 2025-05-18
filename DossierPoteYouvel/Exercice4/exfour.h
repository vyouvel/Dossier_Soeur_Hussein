#ifndef EXFOUR_H
#define EXFOUR_H

#include "../Exercice2/extwo.h"
#include "../Exercice3/exthree.h"

// Déclaration de la structure représentant le CPU
typedef struct CPU
{
    MemoryHandler *memory_handler; // gestionnaire de mémoire : segments, pile, etc.
    HashMap *context; // registre du processeur (AX, BX, IP, ZF, etc.)
    HashMap *constant_pool; // valeurs immédiates pour éviter des malloc inutiles
} CPU;

CPU *cpu_init(int);
void cpu_destroy(CPU *);
void *store(MemoryHandler *, const char *, int, void *);
void *load(MemoryHandler *, const char *, int);
void allocate_variables(CPU *, Instruction **, int);
void print_data_segment(CPU *);
void *register_addressing(CPU *, const char *);
void *memory_direct_addressing(CPU *, const char *);
void *register_indirect_addressing(CPU *, const char *);
void *resolve_addressing(CPU *, const char *);
void handle_MOV(CPU *, void *, void *);
void allocate_code_segment(CPU *, Instruction **, int);
int handle_instruction(CPU *, Instruction *, void *, void *);
int execute_instruction(CPU *, Instruction *);
Instruction *fetch_next_instruction(CPU *);
int run_program(CPU *);
int push_value(CPU *, int );
int pop_value(CPU *, int *);
int alloc_es_segment(CPU *);
int free_es_segment(CPU *);
int resolve_constants(ParserResult *);
#endif
