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
    print_results(finished_processes);
    return EXIT_SUCCESS;
}

void print_results(Queue* processes) {
    FILE* results_file = NULL;
	Process* current = NULL;
	results_file = fopen(OUTPUT_FILE_NAME, "w");

	current = processes -> head;	

	while(current != NULL){
        fprintf(
            results_file,
            "ID: %ld | Waiting time: %f | Turnaround time: %f \n", 
            current -> id,
            current -> waiting_time,
            calculate_turnaround_time(current)
        );	
		current = current->next;
	}

	fclose(results_file);
    print_queue(processes);
}

void print_statistics(Queue* processes) {
    print_queue(processes);
}

