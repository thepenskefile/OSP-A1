# Operating Systems Principles - COSC1114 - Assignment 1

Assignment 1 task 2 - Implement three scheduling algorithms

1. First come first serve scheduling (non-preemptive)
2. Shortest job first scheduling (non-preemptive)
3. Round robin (preemptive, by default quantum = 2 and context switch time = 0.1)

## How to run

1. Compile the code by running

   ```
   make
   ```

2. The program takes two command line arguments. The first is the location of the processes file. The second is the scheduling algorithm to run. The command to run takes the following format:

    ```
    ./scheduler [location-of-processes-file] [fcfs | sjf | rr]`
    ```

The processes file has already been included, so the following commands can be run for each algorithm, after running the `make` command in the same directory:

### FCFS

`./scheduler processes fcfs`

### SJF

`./scheduler processes sjf`

### RR

`./scheduler processes fcfs`
