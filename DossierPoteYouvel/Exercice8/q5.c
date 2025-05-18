#include "../Exercice4/exfour.h"

int alloc_es_segment(CPU *cpu)
{
    int *ax = hashmap_get(cpu->context, "AX");
    int *bx = hashmap_get(cpu->context, "BX");
    int *zf = hashmap_get(cpu->context, "ZF");
    int *es = hashmap_get(cpu->context, "ES");

    if (!ax || !bx || !zf || !es)
        return -1;
    int start = find_free_address_strategy(cpu->memory_handler, *ax, *bx);

    if (start == -1)
    {
        *zf = 1;
        return -1;
    }
    *zf = 0;
    *es = start;
    create_segment(cpu->memory_handler, "ES", start, *ax);
    for (int i = 0; i < *ax; i++)
    {
        int *zero = (int *)malloc(sizeof(int));
        *zero = 0;
        store(cpu->memory_handler, "ES", i, zero);
    }
    return 0;
}
