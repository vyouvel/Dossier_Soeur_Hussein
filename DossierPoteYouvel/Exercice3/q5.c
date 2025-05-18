#include "exthree.h"

/*
 * Libère toute la mémoire associée à un ParserResult.
 * Important pour éviter les fuites mémoire.
 */
void free_parser_result(ParserResult *result)
{
    for (int i = 0; i < result->data_count; i++) free(result->data_instructions[i]);
    for (int i = 0; i < result->code_count; i++) free(result->code_instructions[i]);
    free(result->data_instructions);
    free(result->code_instructions);
    hashmap_destroy(result->labels);
    hashmap_destroy(result->memory_locations);
    free(result);
}
