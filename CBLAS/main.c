#include <stdio.h>
#include <cblas.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1000

void manual_dgemm(int n, double* A, double* B, double* C) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            double sum = 0.0;
            for (k = 0; k < n; k++) {
                sum += A[i*n + k] * B[k*n + j];
            }
            C[i*n + j] = sum;
        }
    }
}

int main() {
    int i, j;
    double *A = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *B = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *C = (double *)malloc(SIZE * SIZE * sizeof(double));
    double *D = (double *)malloc(SIZE * SIZE * sizeof(double));

    for (i = 0; i < SIZE * SIZE; i++) {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
        C[i] = 0.0;
        D[i] = 0.0;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A, SIZE, B, SIZE, 0.0, C, SIZE);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used by cblas_dgemm: %lf seconds\n", cpu_time_used);

    start = clock();
    manual_dgemm(SIZE, A, B, D);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm: %lf seconds\n", cpu_time_used);

    free(A);
    free(B);
    free(C);
    free(D);

    return 0;
}