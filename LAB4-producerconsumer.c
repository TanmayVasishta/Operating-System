#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty=3;
int buffer_item = 0;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer(int id) {
    if ((mutex == 1) && (empty != 0)) {
        int value;
        scanf("%d", &value);
        printf("producer %d produced %d\n", id, value);
        mutex = wait(mutex);
        full = signal(full);
        empty = wait(empty);
        buffer_item = value;
        printf("buffer:%d\n", buffer_item);
        mutex = signal(mutex);
    } else {
        printf("buffer is full!\n");
    }
}

void consumer(int id) {
    if ((mutex == 1) && (full != 0)) {
        mutex = wait(mutex);
        full = wait(full);
        empty = signal(empty);
        printf("consumer %d consumed %d\n", id + 1, buffer_item);
        printf("current buffer len: 0\n");
        mutex = signal(mutex);
    } else {
        printf("buffer is empty!\n");
    }
}

int main() {
    int np, nc, cap;

    printf("enter no. of producers:");
    scanf("%d", &np);
    printf("enter no. of consumers:");
    scanf("%d", &nc);
    printf("enter buffer capacity:");
    scanf("%d", &cap);

    empty = cap;

    for (int i = 1; i <= np; i++) {
        printf("producer created: %d\n", i);
    }

    for (int i = 1; i <= nc; i++) {
        printf("consumer created: %d\n", i);
    }

    while (1) {
        producer(1);
        consumer(1);
    }

    return 0;
}
