#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main() {
    struct sockaddr_un addr;
    char buffer[100];
    int sockfd, client_sockfd, ret;

    // create socket
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // bind socket to address
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));
    if (ret == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Server is running. Waiting for clients...\n");

    while (1) {
        // receive message from client
        ret = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (ret == -1) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        printf("Received message: %s\n", buffer);

        // send response back to client
        client_sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (client_sockfd == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }
        ret = sendto(client_sockfd, "Hello from server!", 18, 0, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));
        if (ret == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        close(client_sockfd);
    }

    close(sockfd);

    return 0;
}
