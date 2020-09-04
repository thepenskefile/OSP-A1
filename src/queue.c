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
    Process* pointer = NULL;
    /* If a queue does not exist, a node cannot be added to it */
    if(queue == NULL) {
        printf("\n Queue does not exist \n");
        return FALSE;
    }
    /* If a process does not exist, it cannot be added to the queue */
    if(process == NULL) {
        printf("\n Process does not exist \n");
        return FALSE;
    }
    /* If this is the first item being added to the queue */
    if(queue -> head == NULL) {
        queue -> head = process;
    }
    else {

        if(add_to_end) {
           pointer = queue -> head;
            while(pointer != NULL) {
                if(pointer -> next == NULL) {
                    pointer -> next = process;
                    break;
                }
                pointer = pointer -> next;
            }
            if(process -> id == 200) {
                printf("ADDING TO END 200\n");
            }
        }
        else {
            process -> next = queue -> head;
            queue -> head = process;   
        }
        
    }

    return TRUE;
}

Queue* search_in_queue(Queue* queue, long process_id, Process** previous) {
    Process* pointer;
    Process* temp = NULL;
    Boolean is_found = FALSE;

    while(pointer != NULL) {
        if(pointer -> id == process_id) {
            is_found = true;
            break;
        }
        else {
            temp = pointer;
            pointer = pointer -> next;
        }
    }

    if(is_found == TRUE) {
        if(previous) {
            *previous = temp;
        }
        return pointer;
    }
    else {
        return NULL;
    }
}

int remove_from_queue(Process** head_ref, long process_id) {
    Process* temp = *head_ref, *prev; 
  
    if (temp != NULL && temp->id == process_id) { 
        *head_ref = temp->next;    
        return; 
    } 
  
    while (temp != NULL && temp->id != process_id) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    if (temp == NULL) return; 
  
    prev->next = temp->next; 
  

    /*
    Process* previous = NULL;
    Process* delete = NULL;

    delete = search_in_queue(queue, process_id, &previous);
    if(delete == NULL) {
        return -1;
    }
    else {
        if(previous != NULL) {
            previous -> next = delete -> next;
        }
        if(delete == queue -> head) {
            queue -> head = delete -> next;
        }
    }
    delete = NULL;
    return 0;
    */
}

void print_queue(Queue* queue) {
    Process* print_pointer;

    print_pointer = queue -> head;
    while(print_pointer != NULL) {
        printf(
            "ID: %ld | Waiting time: %f | Turnaround time: %f \n", 
            print_pointer -> id,
            print_pointer -> waiting_time,
            calculate_turnaround_time(print_pointer)
        );
        print_pointer = print_pointer -> next;
    }
}

int count_nodes(Queue* queue) {
    Process* process;
    int count = 0;
    process = queue -> head;
    while(process != NULL) {
        count++;
        process = process -> next;
    }
    return count;
}