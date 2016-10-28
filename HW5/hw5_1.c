#include <math.h>
#include <omp.h> 
#include <stdlib.h>
#include <stdio.h>
#define MAX_THREADS 8

double shubert(double x1, double x2);

int main () { 
    const int MAX_STEPS = 8;
    const int LOWER_BOUND = -2;
    const double STEP_SIZE = 0.5;
    int threadCount = 0;
    int tid = 0;
    int i = 0;
    double x1, x2, y = 0;
    double min = 99;
    
    #pragma omp parallel for private(tid) reduction(min:min)
    for (i = 0; i <= MAX_STEPS; i++) {
        if (tid == 0 && i == 1) {
            threadCount = omp_get_num_threads();
            printf("Number of threads = %d\n", threadCount);
        }
        tid = omp_get_thread_num();
        x1 = STEP_SIZE * i + LOWER_BOUND;
        printf("Thread #%d, i = %d\n", tid, i);
        for (x2 = -2; x2 <= 2; x2 += 0.5) {
            y = shubert(x1, x2);
            min = (y < min) ? y : min;
        }
    }
    printf("Global min = %.2f\n", min);
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
