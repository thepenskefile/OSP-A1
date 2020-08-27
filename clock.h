#ifndef CLOCK_H
#define CLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct clock {
    float current_tick;
} Clock;

Clock* create_clock();
Clock* tick_clock(Clock* clock);

#endif