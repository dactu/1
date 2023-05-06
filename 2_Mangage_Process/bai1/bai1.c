#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid == -1) {
        perror("fork"); // Failed to create new process
        exit(1);
    } else if (pid == 0) {
        // This is the child process (B)
        printf("Child process (B) with PID=%d and PPID=%d\n", getpid(), getppid());
        exit(0);
    } else {
        // This is the parent process (A)
        printf("Parent process (A) with PID=%d and PPID=%d\n", getpid(), getppid());

        // Wait for the child process to terminate
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child process (B) exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process (B) terminated by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
