#include <math.h>
#include <pthread.h>
#include <stdio.h>

void *child();
int globalCounter = 0;
const int BIG_NUM = 100000000;

int main(int argc, char *argv[]) {
    pthread_t tid1;
    pthread_attr_t attr;

    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid1,&attr,child,NULL);
    int counter = 0;
    for (counter = 0; counter < BIG_NUM; counter++) {
        globalCounter++;
    }
    printf("parent counter = %d\n", counter);
    /* now wait for the thread to exit */
    pthread_join(tid1,NULL);

    printf("global counter = %d\n", globalCounter);   
}

void *child() {
    int counter = 0;
    for (counter = 0; counter > -BIG_NUM; counter--) {
        globalCounter--;
    }
    printf("child counter = %d\n", counter);
    pthread_exit(0);
}
