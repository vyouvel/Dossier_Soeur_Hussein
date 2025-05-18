#include "../Exercice4/exfour.h"

// Alloue le segment de code et initialise IP, ZF, SF à 0
void allocate_code_segment(CPU *cpu, Instruction **code, int count)
{
    create_segment(cpu->memory_handler, "CS", 0, count);
    for (int i = 0; i < count; i++)
    {
        store(cpu->memory_handler, "CS", i, code[i]);
    }
    int *ip = (int *)malloc(sizeof(int));
    int *zf = (int *)malloc(sizeof(int));
    int *sf = (int *)malloc(sizeof(int));

    *ip = 0;
    *zf = 0;
    *sf = 0;
    hashmap_insert(cpu->context, "IP", ip);
    hashmap_insert(cpu->context, "ZF", zf);
    hashmap_insert(cpu->context, "SF", sf);
}
