#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[1];
    pid_t pid;
    char buf[1024];

    if (pipe(fd) < 0) {
        fprintf(stderr, "Failed to create pipe\n");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Failed to fork\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(fd[1]);  // Close write end of the pipe

        ssize_t n = read(fd[0], buf, sizeof(buf));
        if (n < 0) {
            fprintf(stderr, "Failed to read from pipe\n");
            exit(1);
        }

        printf("Child received: %s\n", buf);

        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]);  // Close read end of the pipe

        const char *msg = "Hello from parent!";
        ssize_t n = write(fd[1], msg, strlen(msg) + 1);
        if (n < 0) {
            fprintf(stderr, "Failed to write to pipe\n");
            exit(1);
        }

        close(fd[1]);
    }

    return 0;
}
