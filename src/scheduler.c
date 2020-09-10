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
        fprintf(stderr, "Error! Invalid algorithm name. Usage:\n\t%s <process file> <fcfs | sjf | rr>\n", argv[0]);
		exit(EXIT_FAILURE);
    }
    load_processes(processes, file_name);
    finished_processes = run_scheduler(scheduler, processes);
    print_results(finished_processes, scheduler -> algorithm);

    return EXIT_SUCCESS;
}

void print_results(Queue* processes, Algorithm algorithm) {
    FILE* results_file = NULL;
	Process* current = NULL;
    char output_file_name[50];
    const char* algorithm_name = get_algorithm_name(algorithm);

    strcpy(output_file_name,  OUTPUT_FILE_NAME);
    strcat(output_file_name, algorithm_name);
	results_file = fopen(output_file_name, "w");

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


const char* get_algorithm_name(Algorithm algorithm) {
    if(algorithm == FIRST_COME_FIRST_SERVE) {
        return "fcfs";
    }
    else if (algorithm == SHORTEST_JOB_FIRST) {
        return "sjf";
    }
    else if(algorithm == ROUND_ROBIN) {
        return "rr";
    }
}
