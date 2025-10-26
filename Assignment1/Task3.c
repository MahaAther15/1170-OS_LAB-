/*
 ============================================================================
 Name        : Maha Ather
 Registration :23_NTU-CS-1170 
 Task Title  : Task 3 – Number Info Thread
 Description : This program creates a thread that takes an integer number
               as input, then displays the number, its square, and cube.
               The main thread waits for the thread to complete.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Function executed by the thread
void* number_info(void* arg) {
    int num = *((int*)arg);  // Get the integer value passed from main
    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", num * num);
    printf("Thread: Cube   = %d\n", num * num * num);
    pthread_exit(NULL);
}
int main() {
    pthread_t thread;
    int num;
    // Take input from user
    printf("Enter an integer number: ");
    scanf("%d", &num);
    // Create thread and pass the number
    if (pthread_create(&thread, NULL, number_info, &num) != 0) {
        perror("Failed to create thread");
        exit(1);
    }
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    printf("Main thread: Work completed.\n");
    return 0;
}
