#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

double shubert(double x1, double x2);

int main () {
    
    const char *name = "hello";
    const int SIZE = 4096;
    double x1, x2, y = 0;

    int shm_fd;
    pid_t pid;
    void *shared;

    /* create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory segment */
    ftruncate(shm_fd,SIZE);

    /* now map the shared memory segment in the address space of the process */
    shared = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    pid = fork();

    if (pid == 0) {
        for (x1 = -2; x1 < 0; x1 += 0.5) {
            for (x2 = -2; x2 <= 2; x2 += 0.5) {
                y = shubert(x1, x2);
                if (y < atof(shared)) {
                    sprintf(shared, "%.2f", y);
                }
            }
        }
    }
    if (pid > 0) {
        for (x1 = 0; x1 <= 2; x1 += 0.5) {
            for (x2 = -2; x2 <= 2; x2 += 0.5) {
                y = shubert(x1, x2);
                if (y < atof(shared)) {
                    sprintf(shared, "%.2f", y);
                }
            }
        }
        wait(NULL);
        printf("min = %.2f ", atof(shared));
        if (shm_unlink(name) == -1) {
            printf("Error removing %s\n",name);
            exit(-1);
        }
    }
}

double shubert(double x1, double x2) {
        double sum1 = 0; 
        double sum2 = 0;
        int i;
        for (i = 1; i <= 5; i++) {
                sum1 += i * cos((i + 1) * x1 + i);
                sum2 += i * cos((i + 1) * x2 + i);
        }
        return sum1 * sum2;
}
