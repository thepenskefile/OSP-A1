#ifndef SCHEDULER_OPTIONS_H
#define SCHEDULER_OPTIONS_H

#include "utility.h"
#include "process.h"
#include "queue.h" 
#include "scheduler.h"

#define PROCESS_ID_LENGTH 4
#define BURST_TIME_LENGTH 4
#define ARRIVAL_TIME_LENGTH 4
#define FCFS "fcfs"
#define SJF "sjf"
#define RR "rr"

struct _scheduler;

Boolean load_processes(Queue* queue, const char* processes_file_name);
Boolean set_algorithm(struct _scheduler* scheduler, const char* algorithm_name);

#endif