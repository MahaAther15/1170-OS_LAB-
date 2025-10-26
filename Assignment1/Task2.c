/*
 ============================================================================
 Name        : Maha Ather
 Registration : 23-NTU-CS-1170
 Task Title  : Task 2 – Personalized Greeting Thread
 Description : This program creates a single thread that displays a personalized
               greeting message using the user's name passed as an argument.
               The main thread waits for the greeting to complete.
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
// Function executed by the greeting thread
void* greeting_thread(void* arg) {
    char* name = (char*)arg; 
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}
int main() {
    pthread_t thread;
    char name[50];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Main thread: Waiting for greeting…\n");
    // Create the greeting thread
    if (pthread_create(&thread, NULL, greeting_thread, name) != 0) {
        perror("Failed to create thread");
        exit(1);
    }
    // Wait for the greeting thread to finish
    pthread_join(thread, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}
