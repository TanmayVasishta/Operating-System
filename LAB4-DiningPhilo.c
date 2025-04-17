#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 5
sem_t mutex;
sem_t chopstick[MAX];
int totalPhilosophers;
int hungryCount;
int hungryPhilosophers[MAX];
int choice;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    printf("P %d is waiting\n", id + 1);
    sem_wait(&mutex);
    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % totalPhilosophers]);
    printf("P %d is granted to eat\n", id + 1);
    sleep(1);  
    printf("P %d has finished eating\n", id + 1);
    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % totalPhilosophers]);
    sem_post(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread[MAX];
    int i;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &totalPhilosophers);
    printf("How many are hungry: ");
    scanf("%d", &hungryCount);
    for (i = 0; i < hungryCount; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, totalPhilosophers);
        scanf("%d", &hungryPhilosophers[i]);
        hungryPhilosophers[i]--; 
    }
    for (i = 0; i < totalPhilosophers; i++) {
        sem_init(&chopstick[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);
    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 3) {
            break;
        }
        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            for (i = 0; i < hungryCount; i++) {
                for (int j = 0; j < hungryCount; j++) {
                    printf("P %d is waiting\n", hungryPhilosophers[j] + 1);
                }
                int *id = malloc(sizeof(int));
                *id = hungryPhilosophers[i];
                pthread_create(&thread[i], NULL, philosopher, id);
                pthread_join(thread[i], NULL); 
            }
        }
    }
    return 0;
}
