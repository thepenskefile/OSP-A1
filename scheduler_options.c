#include "scheduler_options.h"
#include "scheduler.h"

Boolean load_processes(Scheduler* scheduler, const char* processes_file_name) {
    if(processes_file_name != NULL){
        FILE* processes_file = NULL;
        int file_char_counter = 0;
        char * file_processes_data = NULL;
        char ch;
        char* token = NULL;
        Process* process;

        char input_process_id[PROCESS_ID_LENGTH + EXTRA_SPACES];
        char input_burst_time[BURST_TIME_LENGTH + EXTRA_SPACES];
        char input_arrival_time[ARRIVAL_TIME_LENGTH + EXTRA_SPACES];
        char* pProcess_id = NULL;
        char* pBurst_time = NULL;
        char* pArrival_time = NULL;
        int process_id = 0;
        int burst_time = 0;
        int arrival_time = 0;

        processes_file = fopen(processes_file_name, "r");
        while((ch = fgetc(processes_file)) != EOF) {
            file_char_counter++;
        }

        file_processes_data = malloc(sizeof(char)*(file_char_counter + 2));

        fseek(processes_file, 0, SEEK_SET);

        while(fgets(file_processes_data, (file_char_counter + 2), processes_file)){
            token = strtok(file_processes_data, "\t\n");


            while(token != NULL) {
                strcpy(input_process_id, token);

                token = strtok(NULL, "\t\n");
                strcpy(input_burst_time, token);

                token = strtok(NULL, "\t\n");
                strcpy(input_arrival_time, token);
                
			    process_id = strtol(input_process_id, &pProcess_id, 10);
                burst_time = strtol(input_burst_time, &pBurst_time, 10);
			    arrival_time = strtol(input_arrival_time, &pArrival_time, 10);
                
                process = create_process(process_id, burst_time, arrival_time);                
                
                add_to_queue(scheduler -> waiting_queue, process);                
                token = strtok(NULL, "\t\n");
            }
        }
        fclose(processes_file);
    }

    return FALSE;
}