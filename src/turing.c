#include "turing.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t NUM_STATES = 6;
// This system handles 6 state TMs, so any symbol after 'F' (70) represents a
// 
const uint8_t HLT_SYMBOLS = 71;
const uint8_t NUM_SYMBOLS = 2;
const uint16_t TAPE_LENGTH = UINT16_MAX;
const uint16_t START_POS = (UINT16_MAX >> 1);

// Tests will be conducted on BB6 holdout
// 1RB1LD_1RC0LD_1LD1RE_0LA1LD_0RB0RF_---0RC

void write(uint8_t *tape, size_t index, bool value) {
  if (index >= TAPE_LENGTH - 1) {
    fprintf(stderr, "Error: Index out of bounds!\n");
    return;
  }

  size_t integer_index = floor(index / 8);
  size_t subindex = index % 8;

  if (value)
    tape[integer_index] |= (1 << (7 - subindex));
  else
    tape[integer_index] &= (1 << (7 - subindex));
}

bool read(uint8_t *tape, size_t index) {
  if (index >= TAPE_LENGTH - 1) {
    fprintf(stderr, "Error: Index out of bounds!\n");
    return false;
  }
  if(!tape)
  {
    fprintf(stderr, "Error: Null passed to read!\n");
    return false;
  }

  size_t integer_index = (index / 8);
  size_t subindex = index % 8;

  return (bool)((tape[integer_index] >> (7 - subindex)) & 1U);
}

// Parse a halt instruction "---"
bool parse_halt(char *str) {
  if (str[0] != '-' || str[1] != '-' || str[2] != '-')
    return false;

  str += 3;
  return true;
}

void dump_instruction(Instruction_t i) {
  if (i.error || i.halting)
    return;

  printf("Value: %i%i%c\n", i.write, i.move, i.new_state);
}

Instruction_t parse_instruction(char *str) {
  Instruction_t instruction;
  if (parse_halt(str)) {
    instruction.halting = true;
    return instruction;
  }

  // Parse what value is written to the tape
  instruction.halting = false;
  if (!isdigit(str[0])) {
    instruction.error = true;
    return instruction;
  }
  instruction.write = str[0] - '0';
  str++;

  // Parse which direction the head moves
  if (str[0] == 'R')
    instruction.move = true;
  else if (str[0] == 'L')
    instruction.move = false;
  else {
    instruction.error = true;
    return instruction;
  }
  str++;

  // Parse the next state that the machine transistions to
  instruction.new_state = str[0];
  str++;

  instruction.error = false;
  return instruction;
}

TuringMachine_t *init_turing(char *str) {
  TuringMachine_t *tm = malloc(sizeof(TuringMachine_t));
  if (!tm)
    return NULL;

  // Initialize the turing machine
  tm->head = START_POS;
  tm->state = 'A';

  char *mirror = str;
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < NUM_SYMBOLS; j++) {
      Instruction_t tmp = parse_instruction(mirror);
      printf("Instruction: %i\n", tmp.move);
      if (tmp.error)
        return NULL;

      mirror += 3;
      tm->instructions[i][j] = tmp;
    }

    // Account for the underscore separating states
    if (i < NUM_STATES - 1)
      mirror++;
  }

  // Zero initialize the tape
  memset(tm->tape, 0, TAPE_LENGTH/8);
  return tm;
}
