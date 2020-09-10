#include "scheduler_options.h"

Boolean load_processes(Queue* queue, const char* processes_file_name) {
    FILE* processes_file = NULL;
    Process* process;
    char line[LINE_LENGTH];
    char* token = NULL;
    
    char input_process_id[PROCESS_ID_LENGTH + EXTRA_SPACES];
    char input_burst_time[BURST_TIME_LENGTH + EXTRA_SPACES];
    char input_arrival_time[ARRIVAL_TIME_LENGTH + EXTRA_SPACES];
    char* pProcess_id = NULL;
    char* pBurst_time = NULL;
    char* pArrival_time = NULL;
    int process_id = 0;
    int burst_time = 0;
    int arrival_time = 0;

    if(processes_file_name == NULL) {
        return FALSE;
    }

    processes_file = fopen(processes_file_name, "r");

    if(processes_file == NULL) {
        return FALSE;
    }
    
    /* Read in file line by line */
    while(fgets(line, sizeof(line), processes_file)) {
        token = strtok(line, "\t");
        strcpy(input_process_id, token);
        token = strtok(NULL, "\t");
        strcpy(input_burst_time, token);
        token = strtok(NULL, "\t");
        strcpy(input_arrival_time, token);
        process_id = strtol(input_process_id, &pProcess_id, 10);
        burst_time = strtol(input_burst_time, &pBurst_time, 10);
        arrival_time = strtol(input_arrival_time, &pArrival_time, 10);

        process = create_process(process_id, burst_time, arrival_time);        
        add_to_queue(queue, process, TRUE);                
        token = strtok(NULL, "\t");
    }

    return TRUE;
}

Boolean set_algorithm(Scheduler* scheduler, const char* algorithm_name) {
    if(strcmp(algorithm_name, FCFS) == 0) {
        scheduler -> algorithm = FIRST_COME_FIRST_SERVE;
        return TRUE;
    }
    if(strcmp(algorithm_name, SJF) == 0) {
        scheduler -> algorithm = SHORTEST_JOB_FIRST;
        return TRUE;
    }
    if(strcmp(algorithm_name, RR) == 0) {
        scheduler -> algorithm = ROUND_ROBIN;
        return TRUE;
    }
    return FALSE;
}