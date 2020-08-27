#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "clock.h"
#include "algorithm.h"
#include "scheduler_options.h"

#define NUMBER_ARGUMENTS 3

typedef struct _scheduler {
    Queue* ready_queue;
    Algorithm algorithm;
    Process* current;
} Scheduler;

int run_scheduler(struct _scheduler* scheduler, Queue* processes);
void move_to_ready(Scheduler* scheduler, Queue* processes, Clock* clock);

#endif