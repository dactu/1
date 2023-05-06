#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_STUDENTS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct student {
    char name[50];
    char dob[20];
    char hometown[50];
};

struct student students[MAX_STUDENTS];
int num_students = 0;

void *input_thread(void *arg) {
    while (1) {
        struct student s;
        printf("Enter student information (or type 'q' to quit):\n");
        printf("Full name: ");
        if (fgets(s.name, sizeof(s.name), stdin) == NULL) {
            break;
        }
        s.name[strcspn(s.name, "\n")] = '\0';  // remove trailing newline
        if (strcmp(s.name, "q") == 0) {
            break;
        }
        printf("Date of birth: ");
        if (fgets(s.dob, sizeof(s.dob), stdin) == NULL) {
            break;
        }
        s.dob[strcspn(s.dob, "\n")] = '\0';
        printf("Hometown: ");
        if (fgets(s.hometown, sizeof(s.hometown), stdin) == NULL) {
            break;
        }
        s.hometown[strcspn(s.hometown, "\n")] = '\0';
        pthread_mutex_lock(&mutex);
        students[num_students++] = s;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(NULL);
}

void *write_thread(void *arg) {
    FILE *fp = fopen("infosinhvien.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        pthread_exit(NULL);
    }
    while (1) {
        pthread_mutex_lock(&mutex);
        while (num_students == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        for (int i = 0; i < num_students; i++) {
            fprintf(fp, "%s, %s, %s\n", students[i].name, students[i].dob, students[i].hometown);
        }
        num_students = 0;
        pthread_mutex_unlock(&mutex);
    }
    fclose(fp);
    pthread_exit(NULL);
}

void *read_thread(void *arg) {
    while (1) {
        FILE *fp = fopen("infosinhvien.txt", "r");
        if (fp == NULL) {
            perror("fopen");
            pthread_exit(NULL);
        }
        char line[200];
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        }
        fclose(fp);
        pthread_cond_signal(&cond);
        pthread_mutex_lock(&mutex);
        while (num_students != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, input_thread, NULL);
    pthread_create(&tid2, NULL, write_thread, NULL);
    pthread_create(&tid3, NULL, read_thread, NULL);
    pthread_join(tid1, NULL);
    pthread_cancel(tid2);
    pthread_cancel(tid3);
    return 0;
}
