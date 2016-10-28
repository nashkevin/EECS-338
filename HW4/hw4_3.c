#include <pthread.h>
#include <stdio.h>
#include <math.h>

double shubert(double x1, double x2);

double min; /* this data is shared by the thread(s) */

void *child1(); /* the thread */
void *child2(); /* the thread */

int main(int argc, char *argv[])
{
pthread_t tid1, tid2; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

/* get the default attributes */
pthread_attr_init(&attr);

/* create the threads */
pthread_create(&tid1,&attr,child1,NULL);
pthread_create(&tid2,&attr,child2,NULL);

/* now wait for the thread to exit */
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);

printf("min = %.2f",min);
}

/**
 * Child threads will begin control in one of these functions
 */
void *child1() 
{
    double x1, x2, y = 0;
    for (x1 = -2; x1 < 0; x1 += 0.5) {
        for (x2 = -2; x2 <= 2; x2 += 0.5) {
            y = shubert(x1, x2);
            if (y < min)
                min = y;
        }
    }
    pthread_exit(0);
}

void *child2() 
{
    double x1, x2, y = 0;
    for (x1 = 0; x1 <= 2; x1 += 0.5) {
        for (x2 = -2; x2 <= 2; x2 += 0.5) {
            y = shubert(x1, x2);
            if (y < min)
                min = y;
        }
    }
    pthread_exit(0);
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
