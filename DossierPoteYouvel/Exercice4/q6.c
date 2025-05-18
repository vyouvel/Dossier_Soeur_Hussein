#include "exfour.h"

// Affiche le contenu du segment de données (DS)
void print_data_segment(CPU *cpu) {
    Segment *seg = hashmap_get(cpu->memory_handler->allocated, "DS");
    if (!seg) {
        printf("Segment DS non alloué.\n");
        return;
    }
    printf("Contenu du segment DS :\n");
    for (int i = 0; i < seg->size; i++) {
        int *val = load(cpu->memory_handler, "DS", i);
        if (val) printf("[%d] = %d\n", i, *val);
        else printf("[%d] = NULL\n", i);
    }
}
