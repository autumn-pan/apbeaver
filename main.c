#include "turing.h"
#include "sims/unacc.h"
#include <stdio.h>
#include <string.h>

#define NUM_MODES 3

const char* modes[] = {
    "sim",
    "range",
    "cells"
};

int main(int argc, char **argv) 
{
    if(argc != 3)
    {
        fprintf(stderr, "Error: more than two arguments passed to bb! expected 3.\n");
        exit(EXIT_FAILURE);
    }

    enum MODE_TYPE mode = UNSET;
    // Get selected mode
    for(int i = 0; i < NUM_MODES; i++)
    {
        if(strcmp(argv[1], modes[i]) == 0)
        {
            mode = i;
        }
    }
    if(mode == UNSET)
    {
        fprintf(stderr, "Error: simulator mode '%s' is invalid!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    TuringMachine_t* tm = init_turing(argv[2]);
    unaccelerated_sim(tm, mode);
}
