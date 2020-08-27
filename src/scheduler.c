#include "scheduler.h"

int main(int argc, char ** argv) {
    const char* file_name;
    const char* algorithm;
    Scheduler scheduler;
    Queue* processes;
    Queue* ready_queue;

    scheduler.ready_queue = ready_queue = create_queue();
    scheduler.current = NULL;
    processes = create_queue();

    if(argc != NUMBER_ARGUMENTS){
        fprintf(stderr, "Error! Usage:\n\t%s <process file> <algorithm>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    algorithm = argv[2];

    if(set_algorithm(&scheduler, algorithm) == FALSE) {
        fprintf(stderr, "Error! Invalid algorithm name. Usage:\n\t%s <process file> <algorithm>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    load_processes(processes, file_name);

    /* TESTING ONLY */
    /*
    print_queue(processes);
    */
    run_scheduler(&scheduler, processes);
    return EXIT_SUCCESS;
}

int run_scheduler(Scheduler* scheduler, Queue* processes) {
    Clock* clock;

    clock = create_clock();

    /**
     * Run the scheduler while:
     *  a. There exists processes that have not been moved to the ready queue yet
     *  b. There exists processes that are still in the ready queue
     *  c. There exists a process that is still running 
     * */     
    while((processes -> head != NULL) || (scheduler -> ready_queue -> head != NULL) || (scheduler -> current != NULL)) {
        printf("NODES IN PROCESSES: %d \n", count_nodes(processes));
        printf("NODES IN READY: %d \n", count_nodes(scheduler -> ready_queue));
        move_to_ready(scheduler, processes, clock);
        run_algorithm(scheduler);
        tick_clock(clock);
    }

    return TRUE;

}

void move_to_ready(Scheduler* scheduler, Queue* processes, Clock* clock) {
    Process* current = NULL;
    Process* previous = NULL;
    Process* delete = NULL;

    current = processes -> head;
    while(current != NULL) {
        if(current -> arrival_time == clock -> current_tick) {
            delete = current;
            add_to_queue(scheduler -> ready_queue, current, TRUE);
            if(previous == NULL) {
                processes -> head = current -> next;
                current = current -> next;
            }
            else {
                previous -> next = current -> next;
                current = current -> next;
            }
            free(delete);
        }
        else {
            previous = current;
            current = current -> next; 
        }
    }
}