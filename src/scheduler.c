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
    print_box_stats(finished_processes);
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

void print_statistics(Queue* processes) {
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


void print_box_stats(Queue* processes) {
    Process* current = NULL;
    FILE* results_file = NULL;
    double turnaround_time;
    int onehund=0, twohund=0, threehund=0, fourhund=0, fivehund=0, 
        sixhund=0, sevenhund=0, eighthund=0, ninehund=0, thous=0, 
        thousone=0, thoustwo=0, thousthree=0, thousfour=0, thousfive=0, 
        thoussix=0, thousseven=0, thouseight=0, none=0;

    results_file = fopen("stats", "w");

    current = processes -> head;

    while(current != NULL){
        turnaround_time = current -> waiting_time + current -> burst_time;

        if(turnaround_time <= 100) {
            onehund++;
        }
        else if(turnaround_time <= 200) {
            twohund++;
        }
        else if(turnaround_time <= 300) {
            threehund++;
        }
        else if(turnaround_time <= 400) {
            fourhund++;
        }
        else if(turnaround_time <= 500) {
            fivehund++;
        }
        else if(turnaround_time <= 600) {
            sixhund++;
        }
        else if(turnaround_time <= 700) {
            sevenhund++;
        }
        else if(turnaround_time <= 800) {
            eighthund++;
        }
        else if(turnaround_time <= 900) {
            ninehund++;
        }
        else if(turnaround_time <= 1000) {
            thous++;
        }
        else if(turnaround_time <= 1100) {
            thousone++;
        }
        else if(turnaround_time <= 1200) {
            thoustwo++;
        }
        else if(turnaround_time <= 1300) {
            thousthree++;
        }
        else if(turnaround_time <= 1400) {
            thousfour++;
        }
        else if(turnaround_time <= 1500) {
            thoussix++;
        }
        else if(turnaround_time <= 1700) {
            thousseven++;
        }
        else if(turnaround_time <= 1800) {
            thouseight++;
        }
        else {
            none++;
        }
        current = current->next;
	}

    fprintf(
        results_file,
        "< = 100 | %d \n< = 200 | %d \n< = 300 | %d \n< = 400 | %d \n< = 500 | %d \n< = 600 | %d \n< = 700 | %d \n< = 800 | %d \n< = 900 | %d \n< = 1000 | %d \n< = 1100 | %d \n< = 1200 | %d \n< = 1300 | %d \n< = 1400 | %d \n< = 1500 | %d \n< = 1600 | %d \n< = 1700 | %d \n< = 1800 | %d \nELSE | %d \n", 
        onehund, twohund, threehund, fourhund, fivehund, sixhund, sevenhund, eighthund, ninehund, thous, thousone, thoustwo, thousthree, thousfour, thousfive, thoussix, thousseven, thouseight, none
    );	
    fclose(results_file);
}