#ifndef UNACC_H
#define UNACC_H

#include "turing.h"
#include <stdint.h>

// Unaccelerated turing machine simulation
enum SIM_RESULT { HALTED, OVERFLOWED, TAPE_EXCEEDED };

void unaccelerated_sim(TuringMachine_t *tm);

#endif