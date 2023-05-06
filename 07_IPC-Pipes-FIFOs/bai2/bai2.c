#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Hello, child process!";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) {  // parent process
        // close the unused end of the pipe
        close(fd[READ_END]);

        // write to the pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        // close the write end of the pipe
        close(fd[WRITE_END]);

        printf("Message sent from parent process: %s\n", write_msg);
    } else {  // child process
        // close the unused end of the pipe
        close(fd[WRITE_END]);

        // read from the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);

        // close the read end of the pipe
        close(fd[READ_END]);

        printf("Message received in child process: %s\n", read_msg);
    }

    return 0;
}
