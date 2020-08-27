#include "scheduler.h"
#include "scheduler_options.h"

int main(int argc, char ** argv) {
    const char* file_name;
    const char* algorithm;
    Scheduler scheduler;
    Queue* processes;
    Queue* ready_queue;

    scheduler.ready_queue = ready_queue = create_queue();
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
    print_queue(processes);

    run_scheduler(&scheduler);
    return EXIT_SUCCESS;
}

int run_scheduler(Scheduler* scheduler) {
    Clock* clock;

    clock = create_clock();

    tick_clock(clock);

    return TRUE;

}