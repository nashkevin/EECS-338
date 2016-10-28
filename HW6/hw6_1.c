#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 100000000
#define PARENT 0
#define CHILD 1

int flag[2], turn = PARENT;
int globalCounter = 0;

void *child();

int main(int argc, char *argv[]) {
    pthread_t tid1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid1, &attr, child, NULL);
    flag[PARENT] = 1;
    turn = CHILD;
    while (flag[CHILD] && turn == CHILD);
    int counter = 0;
    for (counter = 0; counter < N; counter++) {
        globalCounter++;
    }
    printf("parent counter = %d\n", counter);
    flag[PARENT] = 0;
    pthread_join(tid1,NULL);
    printf("global counter = %d\n", globalCounter);   
}

void *child() {
    flag[CHILD] = 1;
    turn = PARENT;
    while (flag[PARENT] && turn == PARENT);
    int counter = 0;
    for (counter = 0; counter > -N; counter--) {
        globalCounter--;
    }
    printf("child counter = %d\n", counter);
    flag[CHILD] = 0;
    pthread_exit(0);
}
