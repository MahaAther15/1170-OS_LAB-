#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t computers;
pthread_mutex_t lock;
int compUse[5];   // K = 5 computers

void* student(void* arg) {
    int id = *(int*)arg;

    sem_wait(&computers);

    pthread_mutex_lock(&lock);
    int assigned = -1;
    for (int i = 0; i < 5; i++) {
        if (compUse[i] == 0) {
            compUse[i] = id;
            assigned = i;
            break;
        }
    }
    printf("Student %d using computer %d\n", id, assigned);
    pthread_mutex_unlock(&lock);

    sleep(2);

    pthread_mutex_lock(&lock);
    compUse[assigned] = 0;
    printf("Student %d left computer %d\n", id, assigned);
    pthread_mutex_unlock(&lock);

    sem_post(&computers);
    return NULL;
}

int main() {
    pthread_t s[10];
    int ids[10];

    sem_init(&computers, 0, 5);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++) compUse[i] = 0;

    for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;
        pthread_create(&s[i], NULL, student, &ids[i]);
    }
    for (int i = 0; i < 10; i++) pthread_join(s[i], NULL);

    return 0;
}
