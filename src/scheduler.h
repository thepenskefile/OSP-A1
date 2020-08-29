#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheduler_options.h"
#include "cpu_scheduler.h"

#define NUMBER_ARGUMENTS 3

void print_statistics(Queue* processes);

#endif