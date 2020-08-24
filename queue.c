#include "queue.h"

Queue* create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL) {
        printf("\n Queue creation failed \n");
        return NULL;
    }

    queue -> head = NULL;

    return queue;
}

Boolean add_to_queue(Queue *queue, Process *process) {
    /* If a queue does not exist, a node cannot be added to it */
    if(queue == NULL) {
        printf("\n Queue does not exist \n");
        return FALSE;
    }
    /* If a queue does not exist, a node cannot be added to it */
    if(process == NULL) {
        printf("\n Process does not exist \n");
        return FALSE;
    }
    /* If this is the first item being added to the queue */
    if(queue -> head == NULL) {
        queue -> head = process;
    }
    else {
        process -> next = queue -> head;
        queue -> head = process;
    }

    return TRUE;
}