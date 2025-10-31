#include "./turing_test.h"
#include "turing.h"
#include "sims/unacc.h"
#include <stdio.h>

void test_parser() {
  TuringMachine_t *tm =
      init_turing("1RB1LD_1RC0LD_1LD1RE_0LA1LD_0RB0RF_---0RC");
  printf("Val: %i\n", tm->instructions[0][0].move);
}

void test_sim() {
  TuringMachine_t *tm =
      init_turing("1RB0LD_1RC0RE_0LA0RC_1LB1LD_0LF1RE_---1LA");
  unaccelerated_sim(tm, SIM);
}