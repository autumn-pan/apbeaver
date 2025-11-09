#include "sims/unacc.h"
#include "turing.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_STEPS 1000000000

// Find the next instruction
Instruction_t get_instruction(TuringMachine_t* tm)
{
  int8_t value = read(tm->tape, tm->head);
  if(value == -1)  
  {
    Instruction_t error;
    error.error = true;
    return error;
  }

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
uint64_t unaccelerated_sim(TuringMachine_t *tm, enum MODE_TYPE mode) {
  if (!tm) {
    fprintf(stderr, "Error: Null passed to unaccelerated_sim!\n");
    return 0;
  }

  uint16_t leftmost_cell = (UINT16_MAX/2);
  uint16_t rightmost_cell = (UINT16_MAX/2);

  for(uint64_t s = 0; s < MAX_STEPS; s++) {
    // Track how many unique cells are visited by the machine
    if(mode == CELLS) 
    {
      if (leftmost_cell > tm->head)
      {
        leftmost_cell = tm->head;
      }
      else if (rightmost_cell < tm->head)
      {
        rightmost_cell = tm->head;
      }
    }

    // Check for any halting conditions
    if (tm->head >= TAPE_LENGTH || tm->head < 0) {
      printf("Turing Machine Out Of Bounds at step %i\n", s);
      printf("Head Position: %i\n", tm->head);
      return 0;
    }

    // Get instruction and check if it's halting
    Instruction_t instruction = get_instruction(tm);
    if (instruction.halting) {
      printf("Turing Machine Halted!\n");
      printf("Index: %i\n", s);
      return 0;
    }
    if(instruction.error)
      return 0;

    // Execute the code on the instruction
    if(!write(tm->tape, tm->head, (bool)instruction.write))
      return 0;
      
    tm->state = instruction.new_state;
    // Move the turing machine over by one step
    if(instruction.move == 1) 
      tm->head++;
    else
      tm->head--;
  }

  return rightmost_cell - leftmost_cell;
}