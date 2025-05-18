#include "../Exercice4/exfour.h"

// MOV : copie la valeur de src vers dest
void handle_MOV(CPU *cpu, void *src, void *dest)
{
    if (!src || !dest)
        return;
    *(int *)dest = *(int *)src;
}
