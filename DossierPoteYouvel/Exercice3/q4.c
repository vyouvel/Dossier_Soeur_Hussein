#include "exthree.h"

int main_(int ac, char **av)
{
    if (ac != 2)
        return 84;
    ParserResult *res = parse(av[1]);

    if (!res)
    {
        printf("Erreur de parsing.\n");
        return;
    }
    printf("DATA COUNT: %d\n", res->data_count);
    printf("CODE COUNT: %d\n", res->code_count);
    for (int i = 0; i < res->data_count; i++)
    {
        Instruction *ins = res->data_instructions[i];

        printf("DATA: %s %s %s\n", ins->mnemonic, ins->operand1, ins->operand2);
    }
    for (int i = 0; i < res->code_count; i++)
    {
        Instruction *ins = res->code_instructions[i];

        printf("CODE: %s %s %s\n", ins->mnemonic,
               ins->operand1 ? ins->operand1 : "",
               ins->operand2 ? ins->operand2 : "");
    }
    hashmap_destroy(res->labels);
    hashmap_destroy(res->memory_locations);
    free_parser_result(res);
    return 0;
}
