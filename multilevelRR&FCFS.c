#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;     
    int bt;     
    int at;        
    int queue;     
} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void roundRobin(Process p[], int n, int quantum, int wt[], int tat[], int rt[]) {
    int remaining_bt[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        remaining_bt[i] = p[i].bt;

    int t = 0, completed = 0;
    
    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                if (rt[i] == -1) rt[i] = t;
                
                if (remaining_bt[i] > quantum) {
                    t += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    t += remaining_bt[i];
                    tat[i] = t - p[i].at;
                    wt[i] = tat[i] - p[i].bt;
                    remaining_bt[i] = 0;
                    completed++;
                }
                executed = 1;
            }
        }
        if (!executed) t++;
    }
}

void fcfs(Process p[], int n, int start_time, int wt[], int tat[], int rt[]) {
    int time = start_time;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        rt[i] = time - p[i].at;
        wt[i] = rt[i];
        tat[i] = wt[i] + p[i].bt;
        time += p[i].bt;
    }
}

int main() {
    int n, quantum;
    Process p[MAX_PROCESSES], sys[MAX_PROCESSES], usr[MAX_PROCESSES];
    int sys_count = 0, usr_count = 0;
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], rt[MAX_PROCESSES];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time, Arrival Time and Queue (1=System, 2=User) for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].queue);

        if (p[i].queue == 1)
            sys[sys_count++] = p[i];
        else
            usr[usr_count++] = p[i];

        wt[i] = 0;
        tat[i] = 0;
        rt[i] = -1; 
    }

    printf("Enter time quantum for Round Robin scheduling: ");
    scanf("%d", &quantum);

    sortByArrival(sys, sys_count);
    sortByArrival(usr, usr_count);

    fcfs(sys, sys_count, quantum, wt, tat, rt);
    int last_sys_time = (sys_count > 0) ? tat[sys_count - 1] + sys[sys_count - 1].at : 0;
    fcfs(usr, usr_count, last_sys_time, &wt[sys_count], &tat[sys_count], &rt[sys_count]);

    printf("\nProcess\tQueue\tWaiting Time\tTurn Around Time\tResponse Time\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].queue, wt[i], tat[i], rt[i]);

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
    }
    
    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turn Around Time: %.2f", avg_tat / n);
    printf("\nAverage Response Time: %.2f\n", avg_rt / n);

    return 0;
}
