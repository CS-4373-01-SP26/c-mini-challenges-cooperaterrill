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
double testMult(double a, double b)
{
    return a * b;
}
double testDiv(double a, double b)
{
    return a / b;
}
double testSqrt(double a)
{
    return sqrt(a);
}
double testSin(double a)
{
    return sin(a);
}

int main()
{
    srand(time(NULL));
    // let's generate some random numbers to operate on
    const int N = 40000000;
    const double MAX_NUMBER = 10000000.0;
    double *nums = malloc(N * sizeof(double));
    long totalTime;
    clock_t start, end;
    for (int i = 0; i < N; i++)
    {
        nums[i] = randrange(1, MAX_NUMBER);
    }

    printf("Benchmarking multiplication...\n");
    for (int i = 0; i < N; i += 2)
    {
        testMult(nums[i], nums[i + 1]);
    }
    totalTime = 0;
    for (int i = 0; i < N; i += 2)
    {
        double num1 = nums[i];
        double num2 = nums[i + 1];
        start = clock();
        double res = testMult(num1, num2);
        end = clock();
        totalTime += end - start;
    }
    printf("Total time for %d trials was %ld cycles\n", N / 2, totalTime);

    printf("Benchmarking division...\n");
    for (int i = 0; i < N; i += 2)
    {
        testDiv(nums[i], nums[i + 1]);
    }
    totalTime = 0;
    for (int i = 0; i < N; i += 2)
    {
        double num1 = nums[i];
        double num2 = nums[i + 1];
        start = clock();
        double res = testDiv(num1, num2);
        end = clock();
        totalTime += end - start;
    }
    printf("Total time for %d trials was %ld cycles\n", N / 2, totalTime);

    printf("Benchmarking sqrt...\n");
    for (int i = 0; i < N / 2; i++)
    {
        testSqrt(nums[i]);
    }
    totalTime = 0;
    for (int i = 0; i < N / 2; i++)
    {
        double num1 = nums[i];
        start = clock();
        double res = testSqrt(num1);
        end = clock();
        totalTime += end - start;
    }
    printf("Total time for %d trials was %ld cycles\n", N / 2, totalTime);
    printf("Benchmarking sin...\n");
    for (int i = 0; i < N / 2; i++)
    {
        testSin(nums[i]);
    }
    totalTime = 0;
    for (int i = 0; i < N / 2; i++)
    {
        double num1 = nums[i];
        start = clock();
        double res = testSin(num1);
        end = clock();
        totalTime += end - start;
    }
    printf("Total time for %d trials was %ld cycles\n", N / 2, totalTime);
}