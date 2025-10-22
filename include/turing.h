#ifndef TURING_H
#define TURING_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_STATES 6

enum SIM_RESULT { HALTED, OVERFLOWED, TAPE_EXCEEDED };

typedef struct {
  uint8_t write; // What value to write under the head
  bool move;     // false represents left, true represents right
  uint8_t new_state;
} Instruction_t;

typedef struct {
  Instruction_t instructions[2][6];
  uint32_t head;
  uint8_t state;
} TuringMachine_t;

#endif