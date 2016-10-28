#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 100000000

sem_t sem;
int globalCounter = 0;

void *child();

int main(int argc, char *argv[]) {
    if (sem_init(&sem, 0, 1) < 0) {
        fprintf(stderr, "ERROR: could not initialize semaphore.\n");
        exit(0);
    }
    pthread_t tid1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid1, &attr, child, NULL);
    sem_wait(&sem);
    int counter = 0;
    for (counter = 0; counter < N; counter++) {
        globalCounter++;
    }
    printf("parent counter = %d\n", counter);
    sem_post(&sem);
    pthread_join(tid1,NULL);
    sem_destroy(&sem);
    printf("global counter = %d\n", globalCounter);   
}

void *child() {
    sem_wait(&sem);
    int counter = 0;
    for (counter = 0; counter > -N; counter--) {
        globalCounter--;
    }
    printf("child counter = %d\n", counter);
    sem_post(&sem);
    pthread_exit(0);
}
