#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process runs "date"
        execlp("date", "date", NULL);
        perror("execlp failed");
    } else {
        // Parent waits for child
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}
