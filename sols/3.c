#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
void matVecMult(int *mat, int *vec, int *vecOut, int matRows, int matCols)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    // assuming vec has dimension (matCols, 1)
    // so output vec will have dimension (matRows, 1)
    for (int i = 0; i < matRows; i++)
    {
        int sum = 0;
        for (int j = 0; j < matCols; j++)
        {
            sum += mat[(i * matCols + j)] * vec[j];
        }
        vecOut[i] = sum;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("\nTook %ld nanoseconds\n", (end.tv_sec - start.tv_sec) * 1000000000L + end.tv_nsec - start.tv_nsec);
}

int main()
{
    FILE *file = fopen("../mv.txt", "r");
    if (!file)
    {
        printf("File not found\n");
        return 1;
    }
    char buffer[256];
    int r, c;
    int vlength;
    int line = 0;
    int *mat;
    int *vec;
    int idx = 0;
    while (fgets(buffer, 256, file))
    {
        if (line == 0)
        {
            sscanf(buffer, "%d %d\n", &r, &c);
            mat = malloc(r * c * sizeof(int));
        }
        else if (line <= r)
        {
            // matrix
            int stringIdx = 0;
            for (int i = 0; i < c; i++)
            {
                int charsRead;
                sscanf(&buffer[stringIdx], "%d %n", &mat[idx++], &charsRead);
                stringIdx += charsRead;
            }
            sscanf(&buffer[stringIdx], "\n");
        }
        else if (line == r + 1)
        {
            // vector length
            sscanf(buffer, "%d \n", &vlength);
            vec = malloc(vlength * sizeof(int));
        }
        else
        {
            // vector
            int stringIdx = 0;
            int vecIdx = 0;
            for (int i = 0; i < c; i++)
            {
                int charsRead;
                sscanf(&buffer[stringIdx], "%d %n", &vec[vecIdx++], &charsRead);
                stringIdx += charsRead;
            }
            sscanf(&buffer[stringIdx], "\n");
        }
        line++;
    }
    int *vecOut = malloc(r * sizeof(int));
    matVecMult(mat, vec, vecOut, r, c);
    for (int i = 0; i < r; i++)
    {
        printf("%d ", vecOut[i]);
    }
    free(mat);
    free(vec);
    return 0;
}