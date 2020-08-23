#include "queue.h"

Queue* create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL) {
        printf("\n Queue creation failed \n");
        return NULL;
    }

    queue -> head = NULL;
    queue -> current = NULL;

    return queue;
}

Queue* add_to_queue(Queue *queue, Process *process) {
    /* If a queue does not exist, a node cannot be added to it */
    if(queue == NULL) {
        printf("\n Queue does not exist \n");
        return NULL;
    }

    /* If a queue does not exist, a node cannot be added to it */
    if(process == NULL) {
        printf("\n Process does not exist \n");
        return NULL;
    }

    /* If this is the first item being added to the queue */
    if(queue -> head == NULL) {
        queue -> head = process;
    }

    /* Create a pointer from the last node in the queue to the new node */
    queue -> current -> next = process;

    return queue;
}