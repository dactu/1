#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *(int*) arg;
    printf("Thread %d is waiting for the semaphore.\n", thread_id);
    sem_wait(&semaphore);  // wait for the semaphore
    printf("Thread %d acquired the semaphore.\n", thread_id);
    sleep(2);  // simulate some work
    printf("Thread %d released the semaphore.\n", thread_id);
    sem_post(&semaphore);  // release the semaphore
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    sem_init(&semaphore, 0, 1);  // initialize the semaphore with value 1

    for (i = 0; i < NUM_THREADS; i++) {

        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
          thread_ids[i] = i + 1;
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);  // destroy the semaphore

    return 0;
}
