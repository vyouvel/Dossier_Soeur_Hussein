#include "Exercice4/exfour.h"

int main(int ac, char *av[]) {
    if (ac < 2) {
        return 84;
    }

    ParserResult *parser_result = parse(av[1]);
    if (!parser_result) {
        printf("Erreur lors du parsing du fichier.\n");
        return 84;
    }

    CPU *cpu = cpu_init(1024);
    allocate_variables(cpu, parser_result->data_instructions, parser_result->data_count);

    resolve_constants(parser_result);
    allocate_code_segment(cpu, parser_result->code_instructions, parser_result->code_count);

    run_program(cpu);

    free_parser_result(parser_result);
    cpu_destroy(cpu);
    return 0;
}
