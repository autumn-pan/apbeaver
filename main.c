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

void compute_all_ranges(char* filename)
{
    FILE* file = fopen(filename, "r");
    FILE* output = fopen("output3.txt", "w");

    if(!file)
    {
        fprintf(stderr, "Error: failed to open file '%s'\n", filename);
        return;
    }

    char buffer[128]; 
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        TuringMachine_t* tm = init_turing(buffer);
        uint64_t range = unaccelerated_sim(tm, CELLS);
        printf("Range: %i\n", range);
        char cells[16];
        
        fprintf(output, "%s %i\n", buffer, range);
        fflush(stdout);
        fflush(output);

        free(tm);
    }
}

int main(int argc, char **argv) 
{
    if(argc == 1)
    {
        compute_all_ranges("BB6_holdouts_1618.txt");
        return 0;
    }

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

