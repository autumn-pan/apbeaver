#include "turing.h"
#include "sims/unacc.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    if(argc > 2)
    {
        fprintf(stderr, "Error: more than two arguments passed to bb! expected 2.\n");
        exit(EXIT_FAILURE);
    }

    TuringMachine_t* tm = init_turing(argv[1]);
    unaccelerated_sim(tm);
}
