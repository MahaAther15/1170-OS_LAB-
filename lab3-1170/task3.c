#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>   // required for pid_t

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execlp("ls", "ls", "-l", NULL);
        // This line only runs if execlp fails
        printf("This will not print if exec succeeds.\n");
    } else {
        // Parent process
        printf("Parent still running...\n");
    }

    return 0;
}
