#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_TIME 50  // Maximum simulation time

typedef struct {
    int pid;
    int burst;
    int period;
    int remaining_time;
    int next_arrival;
} Process;

void rate_monotonic_scheduling(Process p[], int n) {
    int time = 0, executed;
    printf("\nRate Monotonic Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", p[i].pid, p[i].burst, p[i].period);

    while (time < MAX_TIME) {
        executed = -1;
        
        for (int i = 0; i < n; i++) {
            if (p[i].next_arrival <= time && p[i].remaining_time > 0) {
                if (executed == -1 || p[i].period < p[executed].period)
                    executed = i;
            }
        }
        
        if (executed != -1) {
            printf("%dms : Task %d is running.\n", time, p[executed].pid);
            p[executed].remaining_time--;
            if (p[executed].remaining_time == 0) {
                p[executed].next_arrival += p[executed].period;
                p[executed].remaining_time = p[executed].burst; // Reset for periodic execution
            }
        }
        time++;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        scanf("%d", &processes[i].burst);
        processes[i].remaining_time = processes[i].burst;
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].period);
        processes[i].next_arrival = 0;
    }

    rate_monotonic_scheduling(processes, n);

    return 0;
}


