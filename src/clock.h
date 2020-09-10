#ifndef CLOCK_H
#define CLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct clock {
    int current_tick;
} Clock;

/* Function to create a clock */
Clock* create_clock();
/* Function to tick a clock by incrementing its current_tick by one */
Clock* tick_clock(Clock* clock);

#endif