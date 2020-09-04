#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"

Process* create_process(long process_id, double burst_time, long arrival_time) {
    Process *process = (Process*)malloc(sizeof(Process));
    if(process == NULL) {
        printf("\n Process creation failed \n");
        return NULL;
    }
    process -> id = process_id;
    process -> burst_time = burst_time;
    process -> arrival_time = arrival_time;
    process -> waiting_time = 0;
    process -> remaining_burst_time = burst_time;
    process -> next = NULL;

    return process;
}

double calculate_turnaround_time(Process* process) {
    return process -> waiting_time + process -> burst_time;
}