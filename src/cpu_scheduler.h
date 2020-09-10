#ifndef CPU_SCHEDULER_H
#define CPU_SCHEDULER_H

#include "process.h"
#include "queue.h"
#include "clock.h"

#define QUANTUM 2
#define CONTEXT_SWITCH 0.1
#define BURST 1

typedef enum {
    FIRST_COME_FIRST_SERVE,
    SHORTEST_JOB_FIRST,
    ROUND_ROBIN
} Algorithm;

typedef struct scheduler {
    Queue* ready_queue;
    Algorithm algorithm;
    Process* current;
    long quantum;
    long quantum_used;
    double context_switch
} Scheduler;

Scheduler* create_scheduler();
Queue* run_scheduler(Scheduler* scheduler, Queue* processes);
void move_to_ready(Scheduler* scheduler, Queue* processes, Clock* clock);
Queue* run_algorithm(Scheduler* scheduler, Queue* finished_processes);
Queue* first_come_first_serve(Scheduler* scheduler, Queue* finished_processes);
Queue* shortest_job_first(Scheduler* scheduler, Queue* finished_processes);
Queue* round_robin(Scheduler* scheduler, Queue* finished_processes);

#endif