#include "scheduler.h"


// 1. file location
// 2. name of the scheduler
int main(int argc, char ** argv) {

    if(argc != NUMBER_ARGUMENTS){
        fprintf(stderr, "Error! Usage:\n\t%s <dat filename>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    // Check command line arguments for which scheduler to run
    // Read in file

    Queue *queue = create_queue();


}