#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid, arrival, burst, priority, remaining_burst;
    int completion, turnaround, waiting;
    bool completed;
} Process;

void priorityScheduling(Process processes[], int n, bool preemptive) {
    int time = 0, completed = 0;
    Process *current = NULL;

    while (completed < n) {
        int highestPriority = 9999, index = -1;

        // Find the highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time) {
                if (processes[i].priority < highestPriority || 
                   (processes[i].priority == highestPriority && !preemptive && index == -1)) {
                    highestPriority = processes[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        current = &processes[index];

        if (preemptive) {
            current->remaining_burst--;
            time++;
            if (current->remaining_burst == 0) {
                current->completion = time;
                current->turnaround = current->completion - current->arrival;
                current->waiting = current->turnaround - current->burst;
                current->completed = true;
                completed++;
            }
        } else {
            time += current->remaining_burst;
            current->completion = time;
            current->turnaround = current->completion - current->arrival;
            current->waiting = current->turnaround - current->burst;
            current->remaining_burst = 0;
            current->completed = true;
            completed++;
        }
    }
}

void printResults(Process processes[], int n, bool preemptive) {
    printf("\n=== %s Priority Scheduling ===\n", preemptive ? "Preemptive" : "Non-Preemptive");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, processes[i].arrival, processes[i].burst, 
               processes[i].priority, processes[i].completion, 
               processes[i].turnaround, processes[i].waiting);
    }
}

void resetProcesses(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_burst = processes[i].burst;
        processes[i].completed = false;
        processes[i].completion = processes[i].turnaround = processes[i].waiting = 0;
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time, burst time, and priority for process %d: ", i + 1);
        processes[i].pid = i + 1;
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
        processes[i].remaining_burst = processes[i].burst;
        processes[i].completed = false;
    }

    // Preemptive Scheduling
    resetProcesses(processes, n);
    priorityScheduling(processes, n, true);
    printResults(processes, n, true);

    // Non-Preemptive Scheduling
    resetProcesses(processes, n);
    priorityScheduling(processes, n, false);
    printResults(processes, n, false);

    return 0;
}
