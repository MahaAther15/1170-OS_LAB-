#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t stations;

void* car(void* arg) {
    int id = *(int*)arg;

    sem_wait(&stations);
    printf("Car %d is WASHING\n", id);

    sleep(3);

    printf("Car %d is DONE\n", id);
    sem_post(&stations);

    return NULL;
}

int main() {
    pthread_t c[6];
    int ids[6];

    sem_init(&stations, 0, 2);

    for (int i = 0; i < 6; i++) {
        ids[i] = i + 1;
        pthread_create(&c[i], NULL, car, &ids[i]);
    }
    for (int i = 0; i < 6; i++) pthread_join(c[i], NULL);

    return 0;
}
