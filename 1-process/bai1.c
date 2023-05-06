#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FILENAME "C:\\Users\\Admin\\Desktop\\cc\\Linux-Programming-N-System-main\\btc\\1-process\\hello.txt"
#define MESSAGE "Hello, world!\n"

int main() {
    pid_t pid;
    int fd;

    // Create a new process
    pid = fork();

    if (pid == -1) {
        perror("fork"); // Failed to create new process
        exit(1);
    } else if (pid == 0) {
        // This is the child process (B)
        char buf[256];
        int n;

        // Open the file for reading
        fd = open(FILENAME, O_RDONLY);

        if (fd == -1) {
            perror("open");
            exit(1);
        }

        // Read the file contents into a buffer
        n = read(fd, buf, sizeof(buf));

        if (n == -1) {
            perror("read");
            exit(1);
        }

        // Print the contents of the buffer to the screen
        printf("Child process (B) read the following from the file:\n%s", buf);

        // Close the file descriptor
        close(fd);
    } else {
        // This is the parent process (A)
        // Create the file for writing
        fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);

        if (fd == -1) {
            perror("open");
            exit(1);
        }

        // Write the message to the file
        if (write(fd, MESSAGE, sizeof(MESSAGE)) == -1) {
            perror("write");
            exit(1);
        }

        // Close the file descriptor
        close(fd);

        // Wait for the child process to terminate
        wait(NULL);
    }

    return 0;
}
