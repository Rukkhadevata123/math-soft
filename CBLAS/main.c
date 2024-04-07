#include <stdio.h>
#include <cblas.h>

int main() {
    int i, j;
    double A[4] = {1.0, 2.0, 3.0, 4.0};  // A = [1 2; 3 4]
    double B[4] = {5.0, 6.0, 7.0, 8.0};  // B = [5 6; 7 8]
    double C[4] = {0.0, 0.0, 0.0, 0.0};  // C = [0 0; 0 0]

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 2, 2, 2, 1.0, A, 2, B, 2, 0.0, C, 2);

    // Print the result
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%lf ", C[i*2 + j]);
        }
        printf("\n");
    }

    return 0;
}