#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    const int BIG_NUM = 100000000;
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
        for (counter = 0; counter > -BIG_NUM; counter--) {
            globalCounter[0]--;
        }
        printf("child counter = %d\n", counter);
    }
    else {
        for (counter = 0; counter < BIG_NUM; counter++) {
            globalCounter[0]++;
        }
        printf("parent counter = %d\n", counter);
        wait(NULL);
        printf("global counter = %d\n", globalCounter[0]);
    }
    return 0;
}