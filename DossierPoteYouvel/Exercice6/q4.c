#include "../Exercice4/exfour.h"

// Gère l’exécution d’une instruction (MOV, ADD, CMP, etc.)
int handle_instruction(CPU *cpu, Instruction *instr, void *src, void *dest)
{
    if (!instr || !instr->mnemonic)
        return 0;
    int *ip = hashmap_get(cpu->context, "IP");
    int *zf = hashmap_get(cpu->context, "ZF");
    int *sf = hashmap_get(cpu->context, "SF");

    if (strcmp(instr->mnemonic, "MOV") == 0)
        handle_MOV(cpu, src, dest);
    else if (strcmp(instr->mnemonic, "ADD") == 0)
        *(int *)dest += *(int *)src;
    else if (strcmp(instr->mnemonic, "CMP") == 0)
    {
        int diff = *(int *)dest - *(int *)src;
        *zf = (diff == 0);
        *sf = (diff < 0);
    }
    else if (strcmp(instr->mnemonic, "JMP") == 0)
    {
        *ip = atoi(instr->operand1);
        return 1;
    }
    else if (strcmp(instr->mnemonic, "JZ") == 0 && *zf)
    {
        *ip = atoi(instr->operand1);
        return 1;
    }
    else if (strcmp(instr->mnemonic, "JNZ") == 0 && !*zf)
    {
        *ip = atoi(instr->operand1);
        return 1;
    }
    else if (strcmp(instr->mnemonic, "HALT") == 0)
    {
        *ip = 256;
        return 1;
    }
    else if (strcmp(instr->mnemonic, "PUSH") == 0)
        return push_value(cpu, src ? *(int *)src : *(int *)hashmap_get(cpu->context, "AX"));
    else if (strcmp(instr->mnemonic, "POP") == 0)
        return pop_value(cpu, dest ? (int *)dest : hashmap_get(cpu->context, "AX"));
    else if (strcmp(instr->mnemonic, "ALLOC") == 0)
        return alloc_es_segment(cpu);
    else if (strcmp(instr->mnemonic, "FREE") == 0)
        return free_es_segment(cpu);

    return 0;
}
