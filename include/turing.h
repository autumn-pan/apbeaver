#ifndef TURING_H
#define TURING_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <gmp.h>

const uint8_t NUM_STATES = 6;
// This system handles 6 state TMs, so any symbol after 'F' (70) represents a halt
const uint8_t HLT_SYMBOLS = 71; 
const uint8_t NUM_SYMBOLS = 2;
const uint32_t TAPE_LENGTH = UINT32_MAX;
const uint32_t START_POS = (UINT32_MAX >> 1);


enum SIM_RESULT { HALTED, OVERFLOWED, TAPE_EXCEEDED };

typedef struct {
  bool error; // Whether or not the instruction was successfully parsed
  bool halting; // Whether or not it is the halt state
  uint8_t write; // What value to write under the head
  bool move;     // false represents left, true represents right
  uint8_t new_state;
} Instruction_t;

typedef struct {
  Instruction_t instructions[2][6];
  mpz_t tape;
  uint32_t head;
  uint8_t state;
} TuringMachine_t;
#endif