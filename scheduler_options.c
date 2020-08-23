#include "scheduler_options.h"
#include "scheduler.h"

Boolean load_processes(Scheduler* Scheduler, const char* processes_file_name) {
    if(processes_file_name != NULL){
        FILE* processes_file = NULL;
        int file_char_counter = 0;
        char * file_processes_data = NULL;
        char ch;
        char* token = NULL;

        char process_id[PROCESS_ID_LENGTH + EXTRA_SPACES];
        char burst_time[BURST_TIME_LENGTH + EXTRA_SPACES];
        char arrival_time[ARRIVAL_TIME_LENGTH + EXTRA_SPACES];

        processes_file = fopen(processes_file_name, "r");
        while((ch = fgetc(processes_file)) != EOF) {
            file_char_counter++;
        }

        file_processes_data = malloc(sizeof(char)*(file_char_counter + 2));

        fseek(processes_file, 0, SEEK_SET);

        while(fgets(file_processes_data, (file_char_counter + 2), processes_file)){
            token = strtok(file_processes_data, "\t\n");


            while(token != NULL) {
                strcpy(process_id, token);
                printf("PROCESS ID: %s\n", process_id);


                /* Go through each process here */
                token = strtok(NULL, "\t\n");
                strcpy(burst_time, token);
                printf("BURST TIME: %s\n", burst_time);

                token = strtok(NULL, "\t\n");
                strcpy(arrival_time, token);
                printf("ARRIVAL TIME: %s\n", arrival_time);

                token = strtok(NULL, "\t\n");
            }
        }
        fclose(processes_file);
    }

    return FALSE;
}