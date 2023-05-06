#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo)
{
    printf("Received SIGINT signal (Ctrl+C)\n");
}

void sigusr1_handler(int signo)
{
    printf("Received SIGUSR1 signal\n");
}

void sigusr2_handler(int signo)
{
    printf("Received SIGUSR2 signal\n");
}

int main()
{
    // Register the signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    printf("Press Ctrl+C to send a SIGINT signal\n");
    printf("Sending SIGUSR1 signal...\n");
    kill(getpid(), SIGUSR1);
    printf("Sending SIGUSR2 signal...\n");
    kill(getpid(), SIGUSR2);

    // Wait for the signals
    while(1) {
        sleep(1);
    }

    return 0;
}
