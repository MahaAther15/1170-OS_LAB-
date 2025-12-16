#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 5
#define PRODUCE_COUNT 3
#define THREADS 2

// Shared buffer and indices
int sharedBuffer[BUF_SIZE];
int writeIndex = 0;
int readIndex = 0;

// Synchronization primitives
sem_t semEmptySlots;
sem_t semFilledSlots;
pthread_mutex_t bufferLock;

// Producer thread function
void* producerTask(void* arg) {
    int producerId = *(int*)arg;

    for (int i = 0; i < PRODUCE_COUNT; i++) {
        int data = producerId * 100 + i;

        // Wait until an empty slot is available
        sem_wait(&semEmptySlots);

        // Lock buffer before accessing it
        pthread_mutex_lock(&bufferLock);

        sharedBuffer[writeIndex] = data;
        printf("Producer %d produced %d at index %d\n",
               producerId, data, writeIndex);

        writeIndex = (writeIndex + 1) % BUF_SIZE;

        // Unlock buffer
        pthread_mutex_unlock(&bufferLock);

        // Signal that a new item is available
        sem_post(&semFilledSlots);

        sleep(1);
    }
    return NULL;
}

// Consumer thread function
void* consumerTask(void* arg) {
    int consumerId = *(int*)arg;

    for (int i = 0; i < PRODUCE_COUNT; i++) {

        // Wait until a filled slot is available
        sem_wait(&semFilledSlots);

        // Lock buffer before accessing it
        pthread_mutex_lock(&bufferLock);

        int data = sharedBuffer[readIndex];
        printf("Consumer %d consumed %d from index %d\n",
               consumerId, data, readIndex);

        readIndex = (readIndex + 1) % BUF_SIZE;

        // Unlock buffer
        pthread_mutex_unlock(&bufferLock);

        // Signal that a slot is now empty
        sem_post(&semEmptySlots);

        sleep(2); // Consumer is slower
    }
    return NULL;
}

int main() {
    pthread_t producers[THREADS], consumers[THREADS];
    int threadIds[THREADS] = {1, 2};

    // Initialize semaphores and mutex
    sem_init(&semEmptySlots, 0, BUF_SIZE);
    sem_init(&semFilledSlots, 0, 0);
    pthread_mutex_init(&bufferLock, NULL);

    // Create producer and consumer threads
    for (int i = 0; i < THREADS; i++) {
        pthread_create(&producers[i], NULL, producerTask, &threadIds[i]);
        pthread_create(&consumers[i], NULL, consumerTask, &threadIds[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < THREADS; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    // Cleanup resources
    sem_destroy(&semEmptySlots);
    sem_destroy(&semFilledSlots);
    pthread_mutex_destroy(&bufferLock);

    return 0;
}
