#include <stdio.h>
#include <cblas.h>
#include <time.h>

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
    double A[4] = {1.0, 2.0, 3.0, 4.0};  // A = [1 2; 3 4]
    double B[4] = {5.0, 6.0, 7.0, 8.0};  // B = [5 6; 7 8]
    double C[4] = {0.0, 0.0, 0.0, 0.0};  // C = [0 0; 0 0]
    double D[4] = {0.0, 0.0, 0.0, 0.0};  // D = [0 0; 0 0]

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 2, 2, 2, 1.0, A, 2, B, 2, 0.0, C, 2);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used by cblas_dgemm: %lf seconds\n", cpu_time_used);

    start = clock();
    manual_dgemm(2, A, B, D);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm: %lf seconds\n", cpu_time_used);

    return 0;
}