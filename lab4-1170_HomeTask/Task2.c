#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int number;
    bool is_prime;
} PrimeData;

void* check_prime(void* arg) {
    PrimeData* data = (PrimeData*)arg;
    int n = data->number;

    if (n <= 1) {
        data->is_prime = false;
        return NULL;
    }

    data->is_prime = true;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            data->is_prime = false;
            break;
        }
    }

    return NULL;
}

int main() {
    PrimeData data;
    pthread_t thread;

    printf("Enter a number to check for prime: ");
    scanf("%d", &data.number);

    pthread_create(&thread, NULL, check_prime, &data);
    pthread_join(thread, NULL);

    if (data.is_prime)
        printf("%d is a prime number.\n", data.number);
    else
        printf("%d is NOT a prime number.\n", data.number);

    return 0;
}
