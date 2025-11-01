#ifndef UNACC_H
#define UNACC_H

#include "turing.h"
#include <stdint.h>

uint64_t unaccelerated_sim(TuringMachine_t *tm, enum MODE_TYPE mode);

#endif