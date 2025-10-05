#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process runs "top"
        execlp("top", "top", NULL);
        perror("execlp failed");
    } else {
        // Parent process waits
        printf("Parent: child PID = %d\n", pid);
        sleep(30); // give time to check with top
    }
    return 0;
}
