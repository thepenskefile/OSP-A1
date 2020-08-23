#ifndef PROCESS_H
#define PROCESS_H

/* A structure to represent a process. Stores the value of the process and a pointer to the next process in a queue */
typedef struct process {
    int value;
    struct process *next;
} Process;

#endif