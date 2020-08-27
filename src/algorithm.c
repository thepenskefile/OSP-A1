#include "algorithm.h"
#include "scheduler.h"

Boolean run_algorithm(Scheduler* scheduler) {
    if(scheduler -> algorithm == FIRST_COME_FIRST_SERVE) {
        return first_come_first_serve(scheduler);
    }
    else if(scheduler -> algorithm == SHORTEST_JOB_FIRST) {
        return shortest_job_first(scheduler);
    }
    else if(scheduler -> algorithm == ROUND_ROBIN) {
        return round_robin(scheduler);
    }

    return FALSE;
}

Boolean first_come_first_serve(Scheduler* scheduler) {
    printf("Running FCFS \n");
    /* If there is no current process running, schedule a new process to begin */
    if(scheduler -> current == NULL) {
        /* The new process to begin running is the first in the queue */
        scheduler -> current = scheduler -> ready_queue -> head;
        /* Remove the running process from the ready queue */
        scheduler -> ready_queue -> head = scheduler -> ready_queue -> head -> next;
    }
    /* The burst time of the currently running process is decreased by one clock tick */
    scheduler -> current -> burst_time--;
    /* If the burst time of the current process is 0, that means the process has finished running
        and can be removed */
    if(scheduler -> current -> burst_time == 0) {
        free(scheduler -> current);
        scheduler -> current = NULL;
    }
    return TRUE;
}

Boolean shortest_job_first(Scheduler* scheduler) {
    /* Implement algorithm here */
    printf("Running SJF \n");
    return TRUE;
}

Boolean round_robin(Scheduler* scheduler) {
    /* Implement algorithm here */
    printf("Running RR \n");
    return TRUE;
}
