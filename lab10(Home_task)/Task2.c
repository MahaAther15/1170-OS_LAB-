#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t downloadSlots;

void* downloadFile(void* arg) {
    int id = *(int*)arg;

    sem_wait(&downloadSlots);
    printf("Download %d STARTED\n", id);

    sleep((rand() % 5) + 1); // 1–5 sec

    printf("Download %d FINISHED\n", id);
    sem_post(&downloadSlots);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t[8];
    int ids[8];

    sem_init(&downloadSlots, 0, 3);

    for (int i = 0; i < 8; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, downloadFile, &ids[i]);
    }
    for (int i = 0; i < 8; i++) pthread_join(t[i], NULL);

    sem_destroy(&downloadSlots);
    return 0;
}
