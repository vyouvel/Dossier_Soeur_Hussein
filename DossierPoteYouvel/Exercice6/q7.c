#include "../Exercice4/exfour.h"

// Exécute tout le programme, instruction par instruction avec pause utilisateur
int run_program(CPU *cpu)
{
    print_data_segment(cpu);
    while (1)
    {
        Instruction *instructions = fetch_next_instruction(cpu);

        if (!instructions)
            break;
        printf("Instruction: %s %s, %s\n", instructions->mnemonic,
               instructions->operand1 ? instructions->operand1 : "", instructions->operand2 ? instructions->operand2 : "");
        execute_instruction(cpu, instructions);
        printf("Appuyez sur Entrée pour continuer ou q pour quitter\n");
        int c = getchar();

        if (c == 'q')
            break;
        while (c != '\n')
            c = getchar();
    }
    print_data_segment(cpu);
    return 0;
}
