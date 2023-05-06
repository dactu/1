#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHARED_MEM_SIZE 1024

int main() {
    int shm_fd;
    void *shm_ptr;
    const char *message = "Hello, shared memory!";

    // Create shared memory
    shm_fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    // Set the size of the shared memory
    ftruncate(shm_fd, SHARED_MEM_SIZE);

    // Map the shared memory into the address space of the process
    shm_ptr = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Write message to the shared memory
    strcpy((char *)shm_ptr, message);

    // Read message from the shared memory
    printf("Message read from shared memory: %s\n", (char *)shm_ptr);

    // Unmap and close the shared memory
    munmap(shm_ptr, SHARED_MEM_SIZE);
    close(shm_fd);

    // Remove the shared memory object
    shm_unlink("/my_shm");

    return 0;
}
