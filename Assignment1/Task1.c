/*
 ============================================================================
 Name        : Maha Ather
 Registration : 23-NTU-CS-1170
 Task Title  : Task 1 – Thread Information Display
 Description : This program creates 5 threads. Each thread prints:
               • Its thread ID usinga pthread_self()
               • Its thread number (1st, 2nd, etc.)
               • Sleeps for a random time (1–3 seconds)
               • Prints a completion message before exiting
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>   
#include <time.h>
void* thread_function(void* arg) {
    int thread_num = *((int*)arg); // Get thread number
    pthread_t tid = pthread_self(); // Get thread ID
    // Generate random sleep time between 1–3 seconds
    int sleep_time = (rand() % 3) + 1;
    printf("Thread %d started (Thread ID: %lu)\n", thread_num, (unsigned long)tid);
    printf("Thread %d sleeping for %d second(s)...\n", thread_num, sleep_time);
    sleep(sleep_time); // Simulate work
    printf("✅ Thread %d completed after %d second(s).\n\n", thread_num, sleep_time);
    pthread_exit(NULL);
}
int main() {
    pthread_t threads[5];
    int thread_numbers[5];
    srand(time(NULL)); // Seed random number generator
    printf("===== Task 1  Thread Information Display =====\n\n");
    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        thread_numbers[i] = i + 1; // Thread numbers start from 1
        if (pthread_create(&threads[i], NULL, thread_function, &thread_numbers[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }
    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("All threads have finished execution.\n");
    return 0;
}
