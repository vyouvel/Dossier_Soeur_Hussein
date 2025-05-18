#include "../Exercice4/exfour.h"

int push_value(CPU *cpu, int value)
{
    int *sp = hashmap_get(cpu->context, "SP");
    Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");

    if (!sp || !ss || *sp < 0)
        return -1;
    int *value_ = (int *)malloc(sizeof(int));
    *value_ = value;
    store(cpu->memory_handler, "SS", *sp, value_);
    (*sp)--;
    return 0;
}

int pop_value(CPU *cpu, int *dest)
{
    int *sp = hashmap_get(cpu->context, "SP");
    Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");

    if (!sp || !ss || *sp >= 127)
        return -1;
    (*sp)++;
    int *value = load(cpu->memory_handler, "SS", *sp);
    if (value && dest)
        *dest = *value;
    return 0;
}

int handle_instruction(CPU *cpu, Instruction *instr, void *src, void *dest)
{
    if (!instr || !instr->mnemonic)
        return 0;
    int *ip = hashmap_get(cpu->context, "IP");
    int *zf = hashmap_get(cpu->context, "ZF");
    int *sf = hashmap_get(cpu->context, "SF");

    if (strcmp(instr->mnemonic, "MOV") == 0)
    {
        handle_MOV(cpu, src, dest);
    }
    else if (strcmp(instr->mnemonic, "ADD") == 0)
    {
        *(int *)dest += *(int *)src;
    }
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
    else if (strcmp(instr->mnemonic, "JZ") == 0)
    {
        if (*zf)
        {
            *ip = atoi(instr->operand1);
            return 1;
        }
    }
    else if (strcmp(instr->mnemonic, "JNZ") == 0)
    {
        if (!*zf)
        {
            *ip = atoi(instr->operand1);
            return 1;
        }
    }
    else if (strcmp(instr->mnemonic, "HALT") == 0)
    {
        *ip = 256;
        return 1;
    }
    else if (strcmp(instr->mnemonic, "PUSH") == 0)
    {
        int *val = src ? (int *)src : hashmap_get(cpu->context, "AX");

        return push_value(cpu, *val);
    }
    else if (strcmp(instr->mnemonic, "POP") == 0)
    {
        int *target = dest ? (int *)dest : hashmap_get(cpu->context, "AX");

        return pop_value(cpu, target);
    }
    return 0;
}
