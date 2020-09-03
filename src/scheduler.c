#include "scheduler.h"

int main(int argc, char ** argv) {
    const char* file_name;
    const char* algorithm;
    Scheduler* scheduler;
    Queue* processes;
    Queue* finished_processes;

    scheduler = create_scheduler();
    processes = create_queue();

    if(argc != NUMBER_ARGUMENTS){
        fprintf(stderr, "Error! Usage:\n\t%s <process file> <algorithm>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    algorithm = argv[2];

    if(set_algorithm(scheduler, algorithm) == FALSE) {
        fprintf(stderr, "Error! Invalid algorithm name. Usage:\n\t%s <process file> <algorithm>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    load_processes(processes, file_name);

    finished_processes = run_scheduler(scheduler, processes);
    print_statistics(finished_processes);
    return EXIT_SUCCESS;
}

void print_statistics(Queue* processes) {

    print_queue(processes);

    /*
    Process* process;

    process = processes -> head;
    while(process != NULL) {
        printf("WAITING TIME: %ld \n", process -> waiting_time);
        process = process -> next;
    }
    */
}

