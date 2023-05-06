#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork(); // Create a new process

    if (pid == -1) {
        perror("fork"); // Failed to create new process
        exit(1);
    } else if (pid == 0) {
        // This is the child process
        printf("Child process (B) PID: %d\n", getpid());
        printf("Child process (B) PPID: %d\n", getppid());
    } else {
        // This is the parent process
        printf("Parent process (A) PID: %d\n", getpid());
        printf("Parent process (A) PPID: %d\n", getppid());
    }

    return 0;
}
