#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m; // n = number of processes, m = number of resources
    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    int allocation[n][m], max[n][m], available[m];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available matrix:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    int need[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    bool finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        available[k] += allocation[i][k];
                    finish[i] = true;
                    found = true;
                    printf("Process %d can finish.\n", i);
                    count++;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    bool deadlock = false;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock)
        printf("System is in a deadlock state.\n");
    else
        printf("System is not in a deadlock state.\n");

    return 0;
}