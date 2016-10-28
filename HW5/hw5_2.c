#include <math.h>
#include <omp.h> 
#include <stdlib.h>
#include <stdio.h>
#define MAX_THREADS 8

double reduce(double m[]);
double shubert(double x1, double x2);

int main () { 
    const int MAX_STEPS = 8;
    const int LOWER_BOUND = -2;
    const double STEP_SIZE = 0.5;
    int threadCount, tid, i = 0;
    double x1, x2, y, min = 0;
    double minima[MAX_THREADS];
    
    #pragma omp parallel for private(tid) // no reduction
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
            minima[tid] = (y < minima[tid]) ? y : minima[tid];
        }
    }
    min = reduce(minima);
    printf("Global min = %.2f\n", min);
    return 0;
}

double reduce(double m[]) {
    int i;
    double min = 0; 
    for (i = 0; i < MAX_THREADS; i++) {
        min = (m[i] < min) ? m[i] : min;
    }
    return min;
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
