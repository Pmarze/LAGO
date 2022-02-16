#include <stdio.h>
#include <stdlib.h>

#include "rp.h"

int main (int argc, char **argv) {
    rp_pinState_t state;

    // Initialization of API
    if (rp_Init() != RP_OK) {
        fprintf(stderr, "Red Pitaya API init failed!\n");
        return EXIT_FAILURE;
    }

    // configure DIO5_N to input
        rp_DpinSetDirection (RP_DIO5_N, RP_IN);

    // transfer each input state to the corresponding LED state
    while (1) {
        rp_DpinGetState (RP_DIO5_N, &state);
        rp_DpinSetState (RP_LED5, state);
        }
    }

    // Releasing resources
    rp_Release();

    return EXIT_SUCCESS;
}