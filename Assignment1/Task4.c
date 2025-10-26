/*
 ============================================================================
 Name        : Maha Ather
 Registration :23-NTU-CS-1170
 Task Title  : Task 4 – Thread Return Values
 Description : This program creates a thread that calculates the factorial
               of a number entered by the user. The thread returns the result
               using a pointer, and the main thread prints it after joining.
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Thread function to compute factorial
void* factorial(void* arg) {
    int n = *((int*)arg);                  // Get number from argument
    long long *result = malloc(sizeof(long long)); // Allocate memory for result
    *result = 1;
    // Calculate factorial
    for (int i = 1; i <= n; i++) {
        *result *= i;
    }
    pthread_exit((void*)result);           // Return pointer to result
}
int main() {
    pthread_t thread;
    int num;
    long long *fact_result;                // Pointer to store factorial result
    // Take user input
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    // Create a thread to compute factorial
    if (pthread_create(&thread, NULL, factorial, &num) != 0) {
        perror("Thread creation failed");
        return 1;
    }
    // Wait for the thread to finish and get the result
    pthread_join(thread, (void**)&fact_result);
    // Display result
    printf("Factorial of %d is: %lld\n", num, *fact_result);
    printf("Main thread: Computation completed.\n");
    // Free allocated memory
    free(fact_result);
    return 0;
}
