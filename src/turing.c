#include "turing.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

Instruction_t *parse_instruction(char *str) {
  Instruction_t *instruction = malloc(sizeof(Instruction_t));
  if (!instruction) {
    fprintf(stderr, "Error: Memory allocation failed!");
    return NULL;
  }

  if (!isdigit(str[0]))
    return NULL;
  instruction->write = atoi(str[0]);
  str++;

  if (str[0] == "R")
    instruction->move = true;
  else if (str[0] == "L")
    instruction->move = false;
  else
    return NULL;
  str++;

  instruction->new_state = str[0] - 'A';
  return instruction;
}
