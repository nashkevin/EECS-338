#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 100000000
#define PARENT 0
#define CHILD 1

int main() {
    int flag[2], turn = PARENT;
    const char *name = "untitled";
    int shm_fd;
    int *globalCounter;
    int counter;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1);
    globalCounter = mmap(0, 1, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (globalCounter == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }
    pid_t pid;
    pid = fork();
    if (!pid) {
        flag[CHILD] = 1;
        turn = PARENT;
        while (flag[PARENT] && turn == PARENT);
        for (counter = 0; counter > -N; counter--) {
            globalCounter[0]--;
        }
        printf("child counter = %d\n", counter);
        flag[CHILD] = 0;
    }
    else if (pid) {
        flag[PARENT] = 1;
        turn = CHILD;
        while (flag[CHILD] && turn == CHILD);
        for (counter = 0; counter < N; counter++) {
            globalCounter[0]++;
        }
        printf("parent counter = %d\n", counter);
        wait(NULL);
        flag[PARENT] = 0;
        printf("global counter = %d\n", globalCounter[0]);
    }
    return 0;
}