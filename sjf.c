#include <stdio.h>

void nonPreemptiveSJF(int n, int at[], int bt[]) {
    int i, j, time = 0, min, temp;
    int ct[n], wt[n], tat[n], rt[n], completed[n];
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    for (i = 0; i < n; i++) {
        completed[i] = 0;
        rt[i] = -1;
    }

    for (i = 0; i < n; i++) {
        min = -1;
        for (j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= time && (min == -1 || bt[j] < bt[min]))
                min = j;
        }

        if (min == -1) {
            time++;
            i--;
            continue;
        }

        if (rt[min] == -1) {
            rt[min] = time - at[min];
        }

        time += bt[min];
        ct[min] = time;
        tat[min] = ct[min] - at[min];
        wt[min] = tat[min] - bt[min];
        completed[min] = 1;

        totalWT += wt[min];
        totalTAT += tat[min];
        totalRT += rt[min];
    }

    printf("Non-Preemptive SJF Results:\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
    printf("Average TAT: %.2f\n", totalTAT / n);
    printf("Average WT: %.2f\n", totalWT / n);
    printf("Average RT: %.2f\n", totalRT / n);
}

void preemptiveSJF(int n, int at[], int bt[]) {
    int i, time = 0, min, completed = 0;
    int ct[n], wt[n], tat[n], rt[n], remainingBT[n];
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    for (i = 0; i < n; i++) {
        remainingBT[i] = bt[i];
        rt[i] = -1;
    }

    while (completed < n) {
        min = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && remainingBT[i] > 0 && (min == -1 || remainingBT[i] < remainingBT[min]))
                min = i;
        }

        if (min == -1) {
            time++;
            continue;
        }

        if (rt[min] == -1) {
            rt[min] = time - at[min];
        }

        remainingBT[min]--;
        time++;

        if (remainingBT[min] == 0) {
            completed++;
            ct[min] = time;
            tat[min] = ct[min] - at[min];
            wt[min] = tat[min] - bt[min];
            totalWT += wt[min];
            totalTAT += tat[min];
            totalRT += rt[min];
        }
    }

    printf("Preemptive SJF (SRTF) Results:\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
    printf("Average TAT: %.2f\n", totalTAT / n);
    printf("Average WT: %.2f\n", totalWT / n);
    printf("Average RT: %.2f\n", totalRT / n);
}

int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    printf("Choose Scheduling Algorithm:\n1. Non-Preemptive SJF\n2. Preemptive SJF (SRTF)\n");
    scanf("%d", &choice);

    if (choice == 1) {
        nonPreemptiveSJF(n, at, bt);
    } else if (choice == 2) {
        preemptiveSJF(n, at, bt);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

