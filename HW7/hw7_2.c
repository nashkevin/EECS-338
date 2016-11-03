#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 5

/* this data is shared by the thread(s) */
int buffer[BUFFER_SIZE];
int values[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
int N = sizeof values / sizeof *values;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(); /* the thread */
void *consumer(); /* the thread */

int main(int argc, char *argv[]) {
    if (sem_init(&mutex, 0, 1) < 0) {
        fprintf(stderr, "ERROR: could not initialize semaphore.\n");
        exit(0);
    }
    if (sem_init(&empty, 0, N) < 0) {
        fprintf(stderr, "ERROR: could not initialize semaphore.\n");
        exit(0);
    }
    if (sem_init(&full, 0, 0) < 0) {
        fprintf(stderr, "ERROR: could not initialize semaphore.\n");
        exit(0);
    }
    pthread_t tid1, tid2; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the threads */
    pthread_create(&tid1,&attr,producer,NULL);
    pthread_create(&tid2,&attr,consumer,NULL);

    /* now wait for the thread to exit */
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
}

void *producer() {
    int i;
    for (i = 0; i < N; i++) {
        buffer[i % BUFFER_SIZE] = values[i];
    }
    pthread_exit(0);
}

void *consumer() {
    int i;
    for (i = 0; i < N; i++) {
        printf("buffer[%d] = %d\n", i % BUFFER_SIZE, buffer[i % BUFFER_SIZE]);
        buffer[i % N] = 0;
    }
    pthread_exit(0);
}
