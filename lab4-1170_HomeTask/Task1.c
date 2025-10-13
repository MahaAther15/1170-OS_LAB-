#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  

void* print_message(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t tid = pthread_self();

    printf("[Thread %d] ID: %lu - Hello from thread %d!\n", thread_num, tid, thread_num);

    sleep(1); 
    printf("[Thread %d] Finished!\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_nums[3] = {1, 2, 3};

    printf("Main: creating 3 threads...\n");

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_message, &thread_nums[i]);
        printf("Main: started thread %d\n", i + 1);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: joined thread %d\n", i + 1);
    }

    printf("All threads completed. Main thread exiting.\n");
    return 0;
}
