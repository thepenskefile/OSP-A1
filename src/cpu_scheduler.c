#include "cpu_scheduler.h"

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
        printf("NODES IN PROCESSES: %d \n", count_nodes(processes));
        print_queue(processes);
        printf("NODES IN READY: %d \n", count_nodes(scheduler -> ready_queue));
        print_queue(scheduler -> ready_queue);
        if(scheduler -> current != NULL) {
            printf("CURRENT PROCESS = ID: %d | BURST: %d | ARRIVAL: %d \n", scheduler -> current -> id, scheduler -> current -> remaining_burst_time, scheduler -> current -> arrival_time);
        }
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
    printf("Running FCFS \n");
    if(scheduler -> ready_queue -> head == NULL && scheduler -> current == NULL) {
        return finished_processes;
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
        add_to_queue(finished_processes, scheduler -> current, TRUE);
        scheduler -> current = NULL;
    }
    /* Increase the waiting time of each process still in the ready queue by one clock tick */
    process = scheduler -> ready_queue -> head;
    while(process != NULL) {
        process -> waiting_time++;
        process = process -> next;
    }
    return finished_processes;
}

Queue* shortest_job_first(Scheduler* scheduler, Queue* finished_processes) {
    Process* process = NULL;
    Process* previous = NULL;
    Process* previous_shortest_job = NULL;
    Process* shortest_job = NULL;

    printf("Running SJF \n");
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
        process -> waiting_time++;
        process = process -> next;
    }
    return finished_processes;
}

Queue* round_robin(Scheduler* scheduler, Queue* finished_processes) {
    /* Implement algorithm here */
    printf("Running RR \n");
    return finished_processes;
}
