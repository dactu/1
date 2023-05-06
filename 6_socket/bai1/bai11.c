#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main() {
    struct sockaddr_un addr;
    char buffer[100];
    int sockfd, ret;

    // create socket
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // set address of server
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // send message to server
    ret = sendto(sockfd, "Hello from client!", 18, 0, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));
    if (ret == -1) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    // receive response from server
    ret = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (ret == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("Received message from server: %s\n", buffer);

    close(sockfd);

    return 0;
}
