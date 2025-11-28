#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t bridge;
pthread_mutex_t printLock;

void* car(void* arg) {
    int id = *(int*)arg;

    sem_wait(&bridge);

    pthread_mutex_lock(&printLock);
    printf("Car %d ENTERED bridge\n", id);
    pthread_mutex_unlock(&printLock);

    sleep((rand() % 3) + 1);

    pthread_mutex_lock(&printLock);
    printf("Car %d LEFT bridge\n", id);
    pthread_mutex_unlock(&printLock);

    sem_post(&bridge);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t c[10];
    int ids[10];

    sem_init(&bridge, 0, 3);
    pthread_mutex_init(&printLock, NULL);

    for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;
        pthread_create(&c[i], NULL, car, &ids[i]);
    }
    for (int i = 0; i < 10; i++) pthread_join(c[i], NULL);

    return 0;
}
