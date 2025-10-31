#include "sims/unacc.h"
#include "turing.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_STEPS 1000000

void unaccelerated_sim(TuringMachine_t *tm, enum MODE_TYPE mode) {
  if (!tm) {
    fprintf(stderr, "Error: Null passed to unaccelerated_sim!\n");
    return;
  }

  uint64_t overflow = 0;
  uint32_t i = 0;
  uint16_t leftmost_cell = (UINT16_MAX/2);
  uint16_t rightmost_cell = (UINT16_MAX/2);

  for(int s = 0; s < MAX_STEPS; s++) {
    // SIM tracks the number of steps
    if(mode == SIM) {
      i++;
      if(i % UINT32_MAX == 0)
      {
        overflow++;
        printf("Overflow: %i\n", overflow);
        i = 0;
      }      
    }
    else if(mode == CELLS) // count how many cells visited
    {
      if (leftmost_cell > tm->head)
        leftmost_cell = tm->head;
      else if (rightmost_cell < tm->head)
        rightmost_cell = tm->head;
    }

    uint8_t value = (uint8_t)read(tm->tape, tm->head);
    Instruction_t instruction = tm->instructions[tm->state - 'A'][value];

    if (instruction.halting) {
      printf("Turing Machine Halted!\n");
      printf("Overflow: %i\n", overflow);
      printf("Index: %i\n", i);
      return;
    }
    if (tm->head >= TAPE_LENGTH - 1 || tm->head <= 0) {
      printf("Turing Machine Out Of Bounds! (Insufficient Tape Size)\n");
      printf("Head Position: %i\n", tm->head);
      return;
    }

    // Execute the code on the instruction
    write(tm->tape, tm->head, (bool)instruction.write);
    if(instruction.move) 
      tm->head++;
    else
      tm->head--;
    tm->state = instruction.new_state;
  }

  printf("Range: %i\n", rightmost_cell - leftmost_cell);
}