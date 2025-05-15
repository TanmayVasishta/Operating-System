#include <stdio.h>

#define MAX 100

void display(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int search(int key, int frames[], int f) {
    for (int i = 0; i < f; i++)
        if (frames[i] == key) return i;
    return -1;
}

void fifo(int pages[], int n, int f) {
    int frames[MAX], index = 0, pageFaults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames, f) == -1) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }
        display(frames, f);
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

void lru(int pages[], int n, int f) {
    int frames[MAX], used[MAX], time = 0, pageFaults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int pos = search(pages[i], frames, f);
        if (pos == -1) {
            int lruIndex = 0;
            int minTime = MAX;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    lruIndex = j;
                    break;
                } else if (used[j] < minTime) {
                    minTime = used[j];
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            used[lruIndex] = ++time;
            pageFaults++;
        } else {
            used[pos] = ++time;
        }
        display(frames, f);
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

void optimal(int pages[], int n, int f) {
    int frames[MAX], pageFaults = 0;

    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames, f) == -1) {
            int replace = -1, farthest = i;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k == n) {
                    replace = j;
                    break;
                } else if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }
            frames[replace] = pages[i];
            pageFaults++;
        }
        display(frames, f);
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

int main() {
    int n, f;
    int pages[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}