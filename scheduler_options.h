#ifndef SCHEDULER_OPTIONS_H
#define SCHEDULER_OPTIONS_H

#include "utility.h"
#include "scheduler.h"

#define PROCESS_ID_LENGTH 4
#define BURST_TIME_LENGTH 4
#define ARRIVAL_TIME_LENGTH 4

Boolean load_processes(Scheduler* scheduler, const char* processes_file_name);

#endif