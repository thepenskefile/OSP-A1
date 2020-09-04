#include "cpu_scheduler.h"


Scheduler* create_scheduler() {
    Queue* ready_queue;
    Scheduler *scheduler = (Scheduler*)malloc(sizeof(Scheduler));
    
    scheduler -> ready_queue = ready_queue = create_queue();
    scheduler -> current = NULL;
    scheduler -> quantum = QUANTUM;
    scheduler -> quantum_used = 0;
    scheduler -> context_switch = CONTEXT_SWITCH;

    return scheduler;
}

Queue* run_scheduler(Scheduler* scheduler, Queue* processes) {
    Clock* clock;
    Queue* finished_processes;

    finished_processes = create_queue();

    clock = create_clock();
    /**
     * Run the scheduler while:
     *  a. There exists processes that have not been moved to the ready queue yet
     *  b. There exists processes that are still in the ready queue
     *  c. There exists a process that is still running 
     * */     
    while((processes -> head != NULL) || (scheduler -> ready_queue -> head != NULL) || (scheduler -> current != NULL)) {
        move_to_ready(scheduler, processes, clock);
        run_algorithm(scheduler, finished_processes);
        tick_clock(clock);
    }

    return finished_processes;

}

void move_to_ready(Scheduler* scheduler, Queue* processes, Clock* clock) {
    Process* current = NULL;
    Process* previous = NULL;
    Process* remove;

    current = processes -> head;
    while(current != NULL) {
        if(current -> arrival_time == clock -> current_tick) {
            remove = create_process(current -> id, current -> burst_time, current -> arrival_time);
            add_to_queue(scheduler -> ready_queue, remove, TRUE);
            if(previous == NULL) {
                processes -> head = current -> next;
                free(current);
                current = current -> next;
            }
            else {
                previous -> next = current -> next;
                free(current);
                current = current -> next;
            }
        }
        else {
            previous = current;
            current = current -> next; 
        }
    }
}

Queue* run_algorithm(Scheduler* scheduler, Queue* finished_processes) {
    if(scheduler -> algorithm == FIRST_COME_FIRST_SERVE) {
        return first_come_first_serve(scheduler, finished_processes);
    }
    else if(scheduler -> algorithm == SHORTEST_JOB_FIRST) {
        return shortest_job_first(scheduler, finished_processes);
    }
    else if(scheduler -> algorithm == ROUND_ROBIN) {
        return round_robin(scheduler, finished_processes);
    }
    return finished_processes;
}

Queue* first_come_first_serve(Scheduler* scheduler, Queue* finished_processes) {
    Process* process;
    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return finished_processes;
    }
    /* If there is no current process running, schedule a new process to begin */
    if(scheduler -> current == NULL && scheduler -> ready_queue -> head != NULL) {
        /* The new process to begin running is the first in the queue */
        scheduler -> current = scheduler -> ready_queue -> head;
        /* Remove the running process from the ready queue */
        scheduler -> ready_queue -> head = scheduler -> ready_queue -> head -> next;
        scheduler -> current -> next = NULL;
    }
    /* The burst time of the currently running process is decreased by one clock tick */
    scheduler -> current -> remaining_burst_time--;
    /* If the burst time of the current process is 0, that means the process has finished running
        and can be removed */
    if(scheduler -> current -> remaining_burst_time == 0) {
        add_to_queue(finished_processes, scheduler -> current, TRUE);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time = process -> waiting_time + BURST;
        process = process -> next;
    }
    return finished_processes;
}

Queue* shortest_job_first(Scheduler* scheduler, Queue* finished_processes) {
    Process* process = NULL;
    Process* previous = NULL;
    Process* previous_shortest_job = NULL;
    Process* shortest_job = NULL;

    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return finished_processes;
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
        scheduler -> current -> next = NULL;  
    }
    /* The burst time of the currently running process is decreased by one clock tick */
    scheduler -> current -> remaining_burst_time--;
    /* If the burst time of the current process is 0, that means the process has finished running
    and can be removed */
    if(scheduler -> current -> remaining_burst_time == 0) {
        add_to_queue(finished_processes, scheduler -> current, TRUE);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time = process -> waiting_time + BURST;
        process = process -> next;
    }

    return finished_processes;
}

Queue* round_robin(Scheduler* scheduler, Queue* finished_processes) {
    Process* process;
    Boolean context_switch_applied = FALSE;
    Boolean is_first_process = FALSE;

    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return finished_processes;
    }
    
    if(count_nodes(finished_processes) == 0 && scheduler -> current == NULL) {
        is_first_process = TRUE;
    }
    /**
     * Check if maximum quantum has been used on current process. If it has, move it
     * to the end of the ready queue
     * */
    if(scheduler -> current != NULL && scheduler -> quantum_used == QUANTUM) {
        add_to_queue(scheduler -> ready_queue, scheduler -> current, TRUE);
        scheduler -> current = NULL;
        scheduler -> quantum_used = 0;
    }
    /* If there is no current process running, schedule a new process to begin */
    if(scheduler -> current == NULL && scheduler -> ready_queue -> head != NULL) {
        /* The new process to begin running is the first in the queue */
        scheduler -> current = scheduler -> ready_queue -> head;
        /* Remove the running process from the ready queue */
        scheduler -> ready_queue -> head = scheduler -> ready_queue -> head -> next;
        /**
         * Apply context switch to waiting time of current process if:
         * 1. The current process was not the only process in the ready queue
         * 2. The current process was not the first process
         * */
        if(scheduler -> ready_queue -> head != NULL && is_first_process == FALSE) {
            scheduler -> current -> waiting_time = scheduler -> current -> waiting_time + CONTEXT_SWITCH;
            context_switch_applied = TRUE;
        }
        scheduler -> current -> next = NULL;
    }
    if(context_switch_applied == TRUE) {
        scheduler -> current -> remaining_burst_time = 
            scheduler -> current -> remaining_burst_time - (BURST - CONTEXT_SWITCH);
    }
    else {
        scheduler -> current -> remaining_burst_time = scheduler -> current -> remaining_burst_time - BURST;
    }
    scheduler -> quantum_used = scheduler -> quantum_used + BURST;
    /* If the burst time of the current process is 0, that means the process has finished running
    and can be removed */
    if(scheduler -> current -> remaining_burst_time <= 0) {
        add_to_queue(finished_processes, scheduler -> current, TRUE);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time = process -> waiting_time + BURST;
        process = process -> next;
    }
    return finished_processes;
}
