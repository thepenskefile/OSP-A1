#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"
#include "utility.h"

/* A structure to represent a queue of processes. Stores the head process and curent process */
typedef struct queue {
    struct process *head;
} Queue;

/* Initialises a queue */
Queue* create_queue();

/* Adds a node (process) to a queue */
Boolean add_to_queue(Queue *queue, Process *process);

#endif
