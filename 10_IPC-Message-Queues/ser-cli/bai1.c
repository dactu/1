#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 100

// Define the message structure
typedef struct {
    long type;
    char message[MAX_MESSAGE_SIZE];
} message_t;

int main() {
    key_t key = ftok("/tmp", 'A'); // Generate a key for the message queue
    int message_queue_id = msgget(key, IPC_CREAT | 0666); // Create the message queue

    if (message_queue_id == -1) { // Check for errors
        perror("msgget");
        exit(1);
    }

    message_t message;

    // Wait for a message from the client and print it
    while (1) {
        msgrcv(message_queue_id, &message, sizeof(message_t) - sizeof(long), 1, 0);
        printf("Received message: %s\n", message.message);
    }

    return 0;
}
