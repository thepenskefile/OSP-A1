#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"

Process* create_process(int value) {
    Process *process = (Process*)malloc(sizeof(Process));
    if(process == NULL) {
        printf("\n Process creation failed \n");
        return NULL;
    }
    process -> value = value;
    process -> next = NULL;

    return process;
}