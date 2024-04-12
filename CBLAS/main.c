#include <stdio.h>
#include <cblas.h>
#include <time.h>
#include <stdlib.h>
#define BLOCK_SIZE 16

#define SIZE 1600

void manual_dgemm(int n, double *A, double *B, double *C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            double sum = 0.0;
            for (k = 0; k < n; k++)
            {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

void manual_dgemm2(int n, double *A, double *B, double *C)
{
    int i, j, k, i1, j1, k1;
    for (i = 0; i < n; i += BLOCK_SIZE)
    {
        for (j = 0; j < n; j += BLOCK_SIZE)
        {
            for (k = 0; k < n; k += BLOCK_SIZE)
            {
                // mini matrix multiplication
                for (i1 = i; i1 < i + BLOCK_SIZE; ++i1)
                {
                    for (j1 = j; j1 < j + BLOCK_SIZE; ++j1)
                    {
                        double sum = 0.0;
                        for (k1 = k; k1 < k + BLOCK_SIZE; ++k1)
                        {
                            sum += A[i1 * n + k1] * B[k1 * n + j1];
                        }
                        C[i1 * n + j1] += sum;
                    }
                }
            }
        }
    }
}

int main()
{
    int i, j;
    double *A = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *B = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *C = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *D = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *E = (double *)malloc(SIZE * SIZE * sizeof(double));

    C[i] = 0.0;
    D[i] = 0.0;
    E[i] = 0.0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A, SIZE, B, SIZE, 0.0, C, SIZE);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by cblas_dgemm: %lf seconds\n", cpu_time_used);

    start = clock();
    manual_dgemm(SIZE, A, B, D);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm: %lf seconds\n", cpu_time_used);

    start = clock();
    manual_dgemm2(SIZE, A, B, E);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm2: %lf seconds\n", cpu_time_used);

    free(A);
    free(B);
    free(C);
    free(D);
    free(E);

    return 0;
}