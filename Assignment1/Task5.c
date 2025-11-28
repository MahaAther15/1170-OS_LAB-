/*
 ============================================================================
 Name        : Maha Ather
 Registration : (Your Registration Number)
 Task Title  : Task 5 – Struct-Based Thread Communication
 Description : This program simulates a simple student database using threads.
               Each thread receives a Student struct, prints student info, and
               checks if the student qualifies for the Dean’s List (GPA ≥ 3.5).
               The main thread counts how many students made the Dean’s List.
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
// Define Student structure
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Global counter for Dean’s List
int deans_list_count = 0;

// Mutex to safely update global count
pthread_mutex_t lock;

// Thread function
void* check_deans_list(void* arg) {
    Student* s = (Student*)arg;

    printf("\nThread for Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    if (s->gpa >= 3.5) {
        printf("✅ %s made the Dean's List!\n", s->name);

        // Lock before updating shared variable
        pthread_mutex_lock(&lock);
        deans_list_count++;
        pthread_mutex_unlock(&lock);
    } else {
        printf("❌ %s did not make the Dean's List.\n", s->name);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    Student students[3];

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Input data for 3 students
    for (int i = 0; i < 3; i++) {
        printf("\nEnter info for Student %d:\n", i + 1);
        printf("Student ID: ");
        scanf("%d", &students[i].student_id);
        getchar(); // clear newline
        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // remove newline
        printf("GPA: ");
        scanf("%f", &students[i].gpa);
    }

    // Create one thread per student
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, check_deans_list, &students[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display final count
    printf("\n---------------------------------\n");
    printf("Total students on Dean's List: %d\n", deans_list_count);
    printf("Main thread: Task completed.\n");

    // Destroy mutex
    pthread_mutex_destroy(&lock);
    
    return 0;
}
