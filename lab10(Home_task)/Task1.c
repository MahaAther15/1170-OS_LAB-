#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t rooms;                  // counting semaphore
int occupied = 0;             // currently occupied rooms
pthread_mutex_t lock;         // protects occupied variable

void* person(void* arg) {
    int id = *(int*)arg;

    // wait if no room
    sem_wait(&rooms);

    // critical section (entering)
    pthread_mutex_lock(&lock);
    occupied++;
    printf("Person %d entered | Occupied rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    // stay 1–3 seconds
    sleep((rand() % 3) + 1);

    // critical section (leaving)
    pthread_mutex_lock(&lock);
    occupied--;
    printf("Person %d left    | Occupied rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    // release a room
    sem_post(&rooms);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    int N = 3;        // total rooms
    int people = 10;  // total threads

    pthread_t threads[people];
    int ids[people];

    sem_init(&rooms, 0, N);         // initialize semaphore to N rooms
    pthread_mutex_init(&lock, NULL);

    // create threads
    for (int i = 0; i < people; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, person, &ids[i]);
    }

    // wait for all
    for (int i = 0; i < people; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&rooms);
    pthread_mutex_destroy(&lock);

    return 0;
}
