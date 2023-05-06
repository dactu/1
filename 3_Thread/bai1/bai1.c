#include <stdio.h>
#include <pthread.h>

struct human {
    char Hovaten[50];
    int birth_year;
    char sdt[20];
    char nha[50];
};

void *thread_handle(void *arg) {
    int thread_id = *(int *)arg;

    if (thread_id == 1) {
        printf("Thread 1 is huying\n");
    } else if (thread_id == 2) {
        struct human person = {
            .Hovaten = "Tu",
            .birth_year = 2001,
            .sdt = "1234567890",
            .nha = "Ha Noi"
        };
        printf("Thread 2 is huying\n");
        printf("Person info:\nHovaten: %s\nBirth Year: %d\nPhone Number: %s\nQue Quan: %s\n", person.Hovaten, person.birth_year, person.sdt, person.nha);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int tid1 = 1, tid2 = 2;

    pthread_create(&thread1, NULL, thread_handle, &tid1);
    pthread_create(&thread2, NULL, thread_handle, &tid2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
