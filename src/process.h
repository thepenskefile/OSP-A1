#ifndef PROCESS_H
#define PROCESS_H

/* A structure to represent a process. Stores the value of the process and a pointer to the next process in a queue */
typedef struct process {
    long id;
    long burst_time;
    long arrival_time;
    float waiting_time;
    struct process *next;
} Process;

/* Function that returns pointer to process created with passed parameters */
Process* create_process(long process_id, long burst_time, long arrival_time);

#endif