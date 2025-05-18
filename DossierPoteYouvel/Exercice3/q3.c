#include "exthree.h"
#include <stdbool.h>

/*
 * Parse un fichier .asm complet.
 * Identifie les sections .DATA et .CODE
 * Puis appelle les fonctions de parsing appropriées pour chaque ligne.
 */
ParserResult *parse(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
        return NULL;
    ParserResult *result = (ParserResult *)malloc(sizeof(ParserResult));

    // Allocation des tableaux (on suppose max 64 instructions)
    result->data_instructions = (Instruction *)malloc(sizeof(Instruction) * 64);
    result->code_instructions = (Instruction *)malloc(sizeof(Instruction) * 64);
    result->data_count = 0;
    result->code_count = 0;
    result->labels = hashmap_create();
    result->memory_locations = hashmap_create();
    char line[256];
    int current_address = 0;
    bool data_instr = false;
    bool code_instr = false;

    // Lecture ligne par ligne
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, ".DATA"))
        {
            data_instr = true;
            code_instr = false;
        }
        else if (strstr(line, ".CODE"))
        {
            code_instr = true;
            data_instr = false;
        }
        else if (data_instr)
        {
            result->data_instructions[result->data_count++] = parse_data_instruction(line, result->memory_locations, &current_address);
        }
        else if (code_instr)
        {
            result->code_instructions[result->code_count++] = parse_code_instruction(line, result->labels, result->code_count);
        }
    }
    fclose(file);
    return result;
}
