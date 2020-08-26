#include "scheduler.h"
#include "scheduler_options.h"

/* 1. file location */
/* 2. name of the scheduler */
int main(int argc, char ** argv) {
    const char* file_name;
    const char* algorithm;
    Scheduler scheduler;
    Queue* ready_queue;
    /* TESTING */
    Process* debug_pointer;

    scheduler.ready_queue = ready_queue = create_queue();

    printf("ARGC: %d\n", argc);

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

    load_processes(&scheduler, file_name);

    /* TESTING ONLY */
    debug_pointer = scheduler.ready_queue->head;
    while(debug_pointer != NULL) {
        printf("ID: %ld\n", debug_pointer->id);
        debug_pointer = debug_pointer -> next;
    }
    printf("ALGORITHM: %d\n", (int)scheduler.algorithm);

    run_scheduler(&scheduler);
    return EXIT_SUCCESS;
}

int run_scheduler(Scheduler* scheduler) {
    Clock* clock;

    clock = create_clock();

    tick_clock(clock);

    return TRUE;

}