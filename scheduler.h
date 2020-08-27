#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "queue.h"
#include "clock.h"

#define NUMBER_ARGUMENTS 3
typedef enum scheduler_algorithm {
    FIRST_COME_FIRST_SERVE,
    SHORTEST_JOB_FIRST,
    ROUND_ROBIN
} Algorithm;

typedef struct scheduler {
    Queue* ready_queue;
    Algorithm algorithm;
} Scheduler;

int run_scheduler(Scheduler* scheduler);

#endif