#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utility.h"

typedef enum {
    FIRST_COME_FIRST_SERVE,
    SHORTEST_JOB_FIRST,
    ROUND_ROBIN
} Algorithm;

struct _scheduler;

Boolean run_algorithm(struct _scheduler* scheduler);
Boolean first_come_first_serve(struct _scheduler* scheduler);
Boolean shortest_job_first(struct _scheduler* scheduler);
Boolean round_robin(struct _scheduler* scheduler);

#endif