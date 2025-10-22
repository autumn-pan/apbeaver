#include "turing.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Tests will be conducted on BB6 holdout
// 1RB1LD_1RC0LD_1LD1RE_0LA1LD_0RB0RF_---0RC

// Parse a halt instruction "---"
bool parse_halt(char *str)
{
  if(str[0] != '-' || str[1] != '-' || str[2] != '-')
    return false;

  str += 3;
  return true;
}

Instruction_t parse_instruction(char *str) {
  Instruction_t instruction;
  if(parse_halt(str))
  {
    instruction.halting = true;
    return instruction;
  }

  instruction.halting = false;
  if (!isdigit(str[0]))
  {
    instruction.error = true;
    return instruction;
  }

  instruction.write = str[0] - '0';
  str++;

  if (str[0] == 'R')
    instruction.move = true;
  else if (str[0] == 'L')
    instruction.move = false;
  else
  {
    instruction.error = true;
    return instruction;
  }

  str++;
  instruction.new_state = str[0] - 'A';
  if(instruction.new_state >= HLT_SYMBOLS)
    instruction.halting = true;
  
  str++;
  instruction.error = false;

  return instruction;
}

TuringMachine_t *init_turing(char *str) {
  TuringMachine_t *tm = malloc(sizeof(TuringMachine_t));
  if (!tm)
    return NULL;

  // Initialize the tape
  mpz_init_set_ui(tm->tape, 0);
  tm->head = START_POS;

  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 2; j < NUM_SYMBOLS; j++) {
      Instruction_t tmp = parse_instruction(str);
      if(tmp.error)
        return NULL;

      tm->instructions[i][j] = tmp;
    }

    // Account for the underscore separating states
    if(i < NUM_STATES - 1)
      str++;
  }

  return tm;
}