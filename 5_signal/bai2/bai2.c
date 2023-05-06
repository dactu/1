#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    // Check if SIGINT is blocked
    sigset_t old_mask, new_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        perror("sigprocmask");
        return 1;
    }
    int is_blocked = sigismember(&old_mask, SIGINT);
    printf("SIGINT is %sblocked\n", is_blocked ? "" : "not ");

    // Toggle the blocking state of SIGINT
    if (is_blocked) {
        if (sigprocmask(SIG_UNBLOCK, &new_mask, NULL) < 0) {
            perror("sigprocmask");
            return 1;
        }
        printf("Unblocked SIGINT\n");
    } else {
        if (sigprocmask(SIG_BLOCK, &new_mask, NULL) < 0) {
            perror("sigprocmask");
            return 1;
        }
        printf("Blocked SIGINT\n");
    }

    // Wait for the signal
    while(1) {
        sleep(1);
    }

    return 0;
}
