#include "sims/unacc.h"
#include "turing.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_STEPS 1000000000

// Find the next instruction
Instruction_t get_instruction(TuringMachine_t* tm)
{
  // Value is logically incapable of being out of bounds, so no check is needed
  uint8_t value = read(tm->tape, tm->head);

  // Ensure that the instruction indices are within bounds
  if(tm->state < 'A' || tm->state - 'A' >= NUM_STATES)
  {
    fprintf(stderr, "Error: Turing machine state '%s' is out of bounds!\n", tm->state);
    exit(EXIT_FAILURE);
  }
  Instruction_t instruction = tm->instructions[tm->state - 'A'][value];
  return instruction;
}

// Overflow tracking is not necessary for now because it's not meant to track more than 2^64 steps
// Adding it is trivial
void unaccelerated_sim(TuringMachine_t *tm, enum MODE_TYPE mode) {
  if (!tm) {
    fprintf(stderr, "Error: Null passed to unaccelerated_sim!\n");
    return;
  }

  uint16_t leftmost_cell = (UINT16_MAX/2);
  uint16_t rightmost_cell = (UINT16_MAX/2);

  for(uint64_t s = 0; s < MAX_STEPS; s++) {
    // Track how many unique cells are visited by the machine
    if(mode == CELLS) 
    {
      if (leftmost_cell > tm->head)
        leftmost_cell = tm->head;
      else if (rightmost_cell < tm->head)
        rightmost_cell = tm->head;
    }

    // Check for any halting conditions
    if (tm->head >= TAPE_LENGTH || tm->head < 0) {
      printf("Turing Machine Out Of Bounds at step %i\n", s);
      printf("Head Position: %i\n", tm->head);
      return;
    }

    // Get instruction and check if it's halting
    Instruction_t instruction = get_instruction(tm);
    if (instruction.halting) {
      printf("Turing Machine Halted!\n");
      printf("Index: %i\n", s);
      return;
    }

    // Execute the code on the instruction
    write(tm->tape, tm->head, (bool)instruction.write);
    tm->state = instruction.new_state;
    // Move the turing machine over by one step
    if(instruction.move == 1) 
      tm->head++;
    else
      tm->head--;
  }

  printf("Range: %i\n", rightmost_cell - leftmost_cell);
}