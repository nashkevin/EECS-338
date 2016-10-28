#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100000000

int main() {
    const char *name = "untitled";
    sem_t sem;
    int shm_fd;
    int *shared;
    int counter;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1);
    shared = mmap(0, 1, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared == MAP_FAILED) {
        printf("Map failed\n");
        exit(0);
    }
    if ((shared[1] = sem_init(sem, 1, 1)) < 0) {
        fprintf(stderr, "ERROR: could not initialize semaphore.\n");
        exit(0);
    }
    printf("asd\n");
    pid_t pid;
    pid = fork();
    if (!pid) {
        for (counter = 0; counter > -N; counter--) {
            sem_wait(shared[1]);
            shared[0]--;
            sem_post(shared[1]);
        }
        printf("child counter = %d\n", counter);
    }
    else {
        for (counter = 0; counter < N; counter++) {
            sem_wait(shared[1]);
            shared[0]++;
            sem_post(shared[1]);
        }
        printf("parent counter = %d\n", counter);
        wait(NULL);
        sem_destroy(shared[1]);
        printf("global counter = %d\n", shared[0]);
        if (shm_unlink(name) == -1) {
            printf("Error removing %s\n", name);
            exit(0);
        }
    }
    return 0;
}