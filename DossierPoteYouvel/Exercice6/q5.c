#include "../Exercice4/exfour.h"

// Exécute une instruction complète : résolution + traitement
int execute_instruction(CPU *cpu, Instruction *instr)
{
    if (!instr)
        return 0;
    void *src = resolve_addressing(cpu, instr->operand2);
    void *dest = resolve_addressing(cpu, instr->operand1);

    return handle_instruction(cpu, instr, src, dest);
}
