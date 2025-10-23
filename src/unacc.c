#include "unacc.h"
#include "turing.h"
#include <stdint.h>
#include <stdio.h>

void unaccelerated_sim(TuringMachine_t *tm) {
  if (!tm) {
    fprintf(stderr, "Error: Null passed to unaccelerated_sim!\n");
    return;
  }

  while (1) {
    uint8_t value = (uint8_t)read(tm->tape, tm->head);
    Instruction_t instruction = tm->instructions[tm->state - 'A'][value];

    if (instruction.halting) {
      printf("Turing Machine Halted!\n");
      return;
    }
    if (tm->head >= TAPE_LENGTH - 1 || tm->head <= 0) {
      printf("Turing Machine Out Of Bounds!\n");
      return;
    }

    // Execute the code on the instruction
    write(tm->tape, tm->head, (bool)instruction.write);
    tm->head += (uint8_t)instruction.move;
    tm->state = instruction.new_state;
  }
}