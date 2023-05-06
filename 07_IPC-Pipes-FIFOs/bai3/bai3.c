#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_BUF 1024

int main()//reader
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    printf("Reader process waiting for a writer...\n");

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Reader process received message: %s\n", buf);
    close(fd);

    return 0;
}
