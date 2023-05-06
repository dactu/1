#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void write_to_file(char *msg) {
    int fd = open("file.txt", O_WRONLY | O_APPEND | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, msg, strlen(msg));
    close(fd);
}

void process_b() {
    pid_t pid_b = getpid();
    pid_t pid_b_prime, pid_c_prime;

    // Create process B'
    pid_b_prime = fork();
    if (pid_b_prime == -1) {
        perror("fork");
        exit(1);
    } else if (pid_b_prime == 0) {
        write_to_file("Hello I'm B' process\n");
        exit(0);
    }

    // Create process C'
    pid_c_prime = fork();
    if (pid_c_prime == -1) {
        perror("fork");
        exit(1);
    } else if (pid_c_prime == 0) {
        write_to_file("Hello I'm C' process\n");
        exit(0);
    }

    // Wait for B' and C' to finish
    int status_b_prime, status_c_prime;
    waitpid(pid_b_prime, &status_b_prime, 0);
    waitpid(pid_c_prime, &status_c_prime, 0);

    write_to_file("Hello I'm B process\n");
    exit(0);
}

void process_c() {
    pid_t pid_c = getpid();
    pid_t pid_b_prime, pid_c_prime;

    // Create process B'
    pid_b_prime = fork();
    if (pid_b_prime == -1) {
        perror("fork");
        exit(1);
    } else if (pid_b_prime == 0) {
        write_to_file("Hello I'm B' process\n");
        exit(0);
    }

    // Create process C'
    pid_c_prime = fork();
    if (pid_c_prime == -1) {
        perror("fork");
        exit(1);
    } else if (pid_c_prime == 0) {
        write_to_file("Hello I'm C' process\n");
        exit(0);
    }

    // Wait for B' and C' to finish
    int status_b_prime, status_c_prime;
    waitpid(pid_b_prime, &status_b_prime, 0);
    waitpid(pid_c_prime, &status_c_prime, 0);

    write_to_file("Hello I'm C process\n");
    exit(0);
}

int main() {
    pid_t pid_b, pid_c;

    // Create process B
    pid_b = fork();
    if (pid_b == -1) {
        perror("fork");
        exit(1);
    } else if (pid_b == 0) {
        process_b();
    }

    // Create process C
    pid_c = fork();
    if (pid_c == -1) {
        perror("fork");
        exit(1);
    } else if (pid_c == 0) {
        process_c();
    }

    // Wait for B to finish
    int status_b;
    waitpid(pid_b, &status_b, 0);

    printf("Process A: Waiting forB to finish writing to file...\n");
printf("Process A: B has finished writing to file\n");

return 0;
}

