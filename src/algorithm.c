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
    Process* process;
    printf("Running FCFS \n");
    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return TRUE;
    }
    /* If there is no current process running, schedule a new process to begin */
    if(scheduler -> current == NULL && scheduler -> ready_queue -> head != NULL) {
        /* The new process to begin running is the first in the queue */
        scheduler -> current = scheduler -> ready_queue -> head;
        /* Remove the running process from the ready queue */
        scheduler -> ready_queue -> head = scheduler -> ready_queue -> head -> next;
    }
    /* The burst time of the currently running process is decreased by one clock tick */
    scheduler -> current -> remaining_burst_time--;
    /* If the burst time of the current process is 0, that means the process has finished running
        and can be removed */
    if(scheduler -> current -> remaining_burst_time == 0) {
        free(scheduler -> current);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time++;
        process = process -> next;
    }
    return TRUE;
}

Boolean shortest_job_first(Scheduler* scheduler) {
    Process* process = NULL;
    Process* previous = NULL;
    Process* previous_shortest_job = NULL;
    Process* shortest_job = NULL;

    printf("Running SJF \n");
    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return TRUE;
    }
    /* If there is no current process running, schedule a new process to begin */
    if(scheduler -> current == NULL && scheduler -> ready_queue -> head != NULL) {
        /* The new process to begin running is that with the shortest burst time in the queue */
        process = scheduler -> ready_queue -> head;
        shortest_job = process;
        while(process != NULL) {
            if(process -> burst_time < shortest_job -> burst_time) {
                previous_shortest_job = previous;
                shortest_job = process;
            }
            previous = process;
            process = process -> next;
        }
        /* Run the shortest job */
        scheduler -> current = shortest_job;
        /* Remove the running process from the ready queue */
        /* If the shortest job was the first process in the queue */
        if(previous_shortest_job == NULL) {
            scheduler -> ready_queue -> head = scheduler -> ready_queue -> head -> next;
        }
        else {
            previous_shortest_job -> next = shortest_job -> next;
        }        
    }
    /* The burst time of the currently running process is decreased by one clock tick */
    scheduler -> current -> remaining_burst_time--;
    /* If the burst time of the current process is 0, that means the process has finished running
    and can be removed */
    if(scheduler -> current -> remaining_burst_time == 0) {
        free(scheduler -> current);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time++;
        process = process -> next;
    }
    return TRUE;
}

Boolean round_robin(Scheduler* scheduler) {
    /* Implement algorithm here */
    printf("Running RR \n");
    return TRUE;
}
