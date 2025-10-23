#include "./turing_test.h"
#include "turing.h"
#include "unacc.h"
#include <stdio.h>

void test_bitset() {
  uint8_t *tape = init_tape(TAPE_LENGTH);
  bool value1 = read(tape, 9);
  printf("Value: %i\n", value1);
  write(tape, 9, 1);
  bool value2 = read(tape, 9);
  printf("Value: %i\n", value2);

  free(tape);
}

void test_parser() {
  TuringMachine_t *tm =
      init_turing("1RB1LD_1RC0LD_1LD1RE_0LA1LD_0RB0RF_---0RC");
  printf("Val: %i\n", tm->instructions[0][0].move);
}

void test_sim() {
  TuringMachine_t *tm =
      init_turing("1RB1LD_1RC0LD_1LD1RE_0LA1LD_0RB0RF_---0RC");
  unaccelerated_sim(tm);
}