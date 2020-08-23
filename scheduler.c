#include "scheduler.h"
#include "scheduler_options.h"


/* 1. file location */
/* 2. name of the scheduler */
int main(int argc, char ** argv) {
    int clock;
    const char* file_name; 
    Scheduler scheduler;

    printf("ARGC: %d\n", argc);


    if(argc != NUMBER_ARGUMENTS){
        fprintf(stderr, "Error! Usage:\n\t%s <dat filename>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    /* const char* selected_algorithm = argv[2]; */


    /* Check command line arguments for which scheduler to run */
    /* Read in file */

    /* Queue *queue = create_queue(); */

    /* scheduler.algorithm = selected_algorithm; */

    load_processes(&scheduler, file_name);

    clock = create_clock();

    tick_clock(clock);

    return EXIT_SUCCESS;
}