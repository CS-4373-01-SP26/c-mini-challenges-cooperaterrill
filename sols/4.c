#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

double randrange(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + rand() / div;
}
int main()
{
    srand(time(NULL));
    // let's generate some random numbers to operate on
    const int N = 400000;
    const double MAX_NUMBER = 10000000.0;
    double *nums = malloc(N * sizeof(double));
    struct timespec start, end;
    volatile double sink;
    double r;
    for (int i = 0; i < N; i++)
    {
        nums[i] = randrange(1, MAX_NUMBER);
    }

    printf("MEASURING THROUGHPUT:\n");
    printf("Benchmarking multiplication...\n");
    r = 0;
    for (int i = 0; i < N; i++)
    {
        r = nums[i] * 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = nums[i] * 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000000L + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking division...\n");
    r = 0;
    for (int i = 0; i < N; i++)
    {
        r = nums[i] / 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = nums[i] / 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking sqrt...\n");
    r = 0;
    for (int i = 0; i < N; i++)
    {
        r = sqrt(nums[i]);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = sqrt(nums[i]);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking sin...\n");
    r = 0;
    for (int i = 0; i < N; i++)
    {
        r = sin(nums[i]);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = sin(nums[i]);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("\n\nMEASURING LATENCY:\n");
    printf("Benchmarking multiplication...\n");
    r = 1.00001;
    for (int i = 0; i < N; i++)
    {
        r *= 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r *= 1.000001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking division...\n");
    r = 1.00001;
    for (int i = 0; i < N; i++)
    {
        r /= 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r /= 1.00001;
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking sqrt...\n");
    r = 1e10;
    for (int i = 0; i < N; i++)
    {
        r = sqrt(r);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = sqrt(r);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);

    printf("Benchmarking sin...\n");
    r = 1;
    for (int i = 0; i < N; i++)
    {
        r = sin(r);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sink = r;
    for (int i = 0; i < N; i++)
    {
        r = sin(r);
        asm volatile("" ::: "memory");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    sink = r;
    printf("Total time for %d trials was %ld microseconds\n", N, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_nsec - start.tv_nsec);
}