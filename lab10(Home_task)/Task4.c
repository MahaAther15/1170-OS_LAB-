#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t workers;

void* task(void* arg) {
    int id = *(int*)arg;

    sem_wait(&workers);
    printf("Task %d STARTED\n", id);

    sleep((rand() % 2) + 1); // 1–2 sec work

    printf("Task %d FINISHED\n", id);
    sem_post(&workers);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t[10];
    int ids[10];

    sem_init(&workers, 0, 3);

    for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, task, &ids[i]);
    }
    for (int i = 0; i < 10; i++) pthread_join(t[i], NULL);

    return 0;
}
