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

Boolean add_to_queue(Queue *queue, Process *process, Boolean add_to_end) {
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
        queue -> end = queue -> head;
    }
    else {

        if(add_to_end) {
            queue -> end -> next = process;
            queue -> end = process;
        }
        else {
            process -> next = queue -> head;
            queue -> head = process;   
        }
        
    }

    return TRUE;
}

void print_queue(Queue* queue) {
    Process* print_pointer;

    print_pointer = queue -> head;
    while(print_pointer != NULL) {
        printf(
            "ID: %ld | Burst time: %ld | Arrival time: %ld \n", 
            print_pointer->id, 
            print_pointer->burst_time, 
            print_pointer->arrival_time
        );
        print_pointer = print_pointer -> next;
    }
}

int count_nodes(Queue* queue) {
    Process* print_pointer;
    int count = 0;
    print_pointer = queue -> head;
    while(print_pointer != NULL) {
        count++;
        print_pointer = print_pointer -> next;
    }
    return count;
}