#include "exfour.h"

// Alloue les variables déclarées dans la section .DATA
void allocate_variables(CPU *cpu, Instruction **data_instructions, int data_count)
{
    int total_size = 0;

    for (int i = 0; i < data_count; i++)
    {
        if (data_instructions[i]->operand2 && strchr(data_instructions[i]->operand2, ','))
        {
            for (char *s = data_instructions[i]->operand2; *s; s++)
                if (*s == ',')
                    total_size++;
        }
        total_size++;
    }

    create_segment(cpu->memory_handler, "DS", 0, total_size);
    int pos = 0;

    for (int i = 0; i < data_count; i++)
    {
        char *value_str = strdup(data_instructions[i]->operand2);
        char *token = strtok(value_str, ",");
        while (token)
        {
            int *value = (int)malloc(sizeof(int));

            *value = atoi(token);
            store(cpu->memory_handler, "DS", pos++, value);
            token = strtok(NULL, ",");
        }
        free(value_str);
    }
}
