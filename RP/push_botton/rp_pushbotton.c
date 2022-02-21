#include <stdio.h>
#include <stdlib.h>

#include "rp.h"

int main (int argc, char **argv) {
    // Variable used to know the state of the push button
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
        // state is a "enum" structure only with RP_LOW and RP_HIGH
        rp_DpinGetState (RP_DIO5_N, &state);
        rp_DpinSetState (RP_LED5, state);
    }

    // Releasing resources
    rp_Release();

    return EXIT_SUCCESS;
}