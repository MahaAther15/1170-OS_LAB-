#include <stdio.h>
#include <unistd.h>

int main() {
    printf("my PID: %d\n", getpid());
    printf("my parent PID: %d\n", getppid());
    return 0;
}
