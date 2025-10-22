#include "turing.h"
#include "./turing_test.h"
#include <stdio.h>

void test_bitset()
{
    uint8_t* tape = init_tape(TAPE_LENGTH);
    bool value1 = read(tape, 2);
    printf("Value: %i\n", value1);
    write(tape, 2, 1);
    bool value2 = read(tape, 2);
    printf("Value: %i\n", value2);

    free(tape);
}