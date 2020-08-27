#include "clock.h"

Clock* create_clock() {
    Clock* clock = (Clock*)malloc(sizeof(Clock));

    if(clock == NULL) {
        printf("\n Clock creation failed \n");
        return NULL;
    }

    clock -> current_tick = 0;
    return clock;
}

Clock* tick_clock(Clock* clock) {
    int current_tick = clock -> current_tick;
    current_tick++;    
    clock -> current_tick = current_tick;
    return clock;
}