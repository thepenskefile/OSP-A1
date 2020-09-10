#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheduler_options.h"
#include "cpu_scheduler.h"

#define NUMBER_ARGUMENTS 3
#define OUTPUT_FILE_NAME "finished_processes_"

void print_results(Queue* processes, Algorithm algorithm);
const char* get_algorithm_name(Algorithm algorithm);

#endif