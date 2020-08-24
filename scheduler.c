#include "scheduler.h"
#include "scheduler_options.h"

/* 1. file location */
/* 2. name of the scheduler */
int main(int argc, char ** argv) {
    int clock;
    const char* file_name; 
    Scheduler scheduler;
    Queue* waiting_queue;
    Queue* ready_queue;

    Process* debug_pointer;

    scheduler.waiting_queue = waiting_queue = create_queue();
    scheduler.ready_queue = ready_queue = create_queue();

    printf("ARGC: %d\n", argc);


    if(argc != NUMBER_ARGUMENTS){
        fprintf(stderr, "Error! Usage:\n\t%s <process filename> <algorithm>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    /* const char* selected_algorithm = argv[2]; */


    /* Check command line arguments for which scheduler to run */
    /* Read in file */

    /* Queue *queue = create_queue(); */

    /* scheduler.algorithm = selected_algorithm; */

    load_processes(&scheduler, file_name);

    /* TESTING ONLY */
    debug_pointer = scheduler.waiting_queue->head;
    while(debug_pointer != NULL) {
        printf("ID: %ld\n", debug_pointer->id);
        debug_pointer = debug_pointer -> next;
    }

    clock = create_clock();

    tick_clock(clock);

    return EXIT_SUCCESS;
}