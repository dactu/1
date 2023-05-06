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
    key_t key = ftok("/tmp", 'A'); // Get the same key as the server
    int message_queue_id = msgget(key, 0666); // Get the message queue

    if (message_queue_id == -1) { // Check for errors
        perror("msgget");
        exit(1);
    }

    message_t message;
    message.type = 1;

    // Send a message to the server
    while (1) {
        printf("Enter message to send: ");
        fgets(message.message, MAX_MESSAGE_SIZE, stdin);
        msgsnd(message_queue_id, &message, sizeof(message_t) - sizeof(long), 0);
    }

    return 0;
}
