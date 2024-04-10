#include <stdio.h>
#include <cblas.h>
#include <time.h>
#include <stdlib.h>
#define BLOCK_SIZE 16
#define SIZE 1600

// 矩阵结构体
typedef struct
{
    int *row_ptr;
    int *col_idx;
    double *values;
    int num_rows;
    int num_cols;
    int num_nonzeros;
} Matrix;

// 创建和初始化Matrix
Matrix *create_and_init_matrix(int num_rows, int num_cols, double density, int sparse)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;
    matrix->num_nonzeros = 0;
    matrix->row_ptr = (int *)calloc((num_rows + 1), sizeof(int));
    matrix->col_idx = NULL;
    matrix->values = NULL;

    if (sparse)
    {
        // 计算非零元素的数量
        int num_nonzeros = (int)(density * matrix->num_rows * matrix->num_cols);
        matrix->num_nonzeros = num_nonzeros;

        // 分配列索引和值数组
        matrix->col_idx = (int *)malloc(num_nonzeros * sizeof(int));
        matrix->values = (double *)malloc(num_nonzeros * sizeof(double));

        // 随机生成非零元素
        for (int i = 0; i < num_nonzeros; i++)
        {
            matrix->col_idx[i] = rand() % matrix->num_cols; // 随机列索引
            matrix->values[i] = (double)rand() / RAND_MAX;  // 随机值
        }

        // 更新行指针数组
        for (int i = 0; i < matrix->num_rows; i++)
        {
            matrix->row_ptr[i + 1] = matrix->row_ptr[i] + (rand() % (num_nonzeros / matrix->num_rows + 1));
        }
        matrix->row_ptr[matrix->num_rows] = num_nonzeros;
    }
    else
    {
        // 初始化密集矩阵
        matrix->values = (double *)malloc(num_rows * num_cols * sizeof(double));
        for (int i = 0; i < num_rows * num_cols; i++)
        {
            matrix->values[i] = (double)rand() / RAND_MAX;
        }
    }

    return matrix;
}

// 释放Matrix
void free_matrix(Matrix *matrix)
{
    free(matrix->row_ptr);
    if (matrix->col_idx != NULL)
    {
        free(matrix->col_idx);
    }
    free(matrix->values);
    free(matrix);
}

void manual_dgemm(Matrix *A, Matrix *B, Matrix *C)
{
    int i, j, k;
    for (i = 0; i < A->num_rows; i++)
    {
        for (j = 0; j < B->num_cols; j++)
        {
            double sum = 0.0;
            for (k = 0; k < A->num_cols; k++)
            {
                sum += A->values[i * A->num_cols + k] * B->values[k * B->num_cols + j];
            }
            C->values[i * C->num_cols + j] = sum;
        }
    }
}

void manual_dgemm2(Matrix *A, Matrix *B, Matrix *C)
{
    int i, j, k, i1, j1, k1;
    for (i = 0; i < A->num_rows; i += BLOCK_SIZE)
    {
        for (j = 0; j < B->num_cols; j += BLOCK_SIZE)
        {
            for (k = 0; k < A->num_cols; k += BLOCK_SIZE)
            {
                // mini matrix multiplication
                for (i1 = i; i1 < i + BLOCK_SIZE; ++i1)
                {
                    for (j1 = j; j1 < j + BLOCK_SIZE; ++j1)
                    {
                        double sum = 0.0;
                        for (k1 = k; k1 < k + BLOCK_SIZE; ++k1)
                        {
                            sum += A->values[i1 * A->num_cols + k1] * B->values[k1 * B->num_cols + j1];
                        }
                        C->values[i1 * C->num_cols + j1] += sum;
                    }
                }
            }
        }
    }
}

void sparse_dgemm(Matrix *A, Matrix *B, Matrix *C)
{
    int i, j, k;
    for (i = 0; i < A->num_rows; i++)
    {
        for (k = A->row_ptr[i]; k < A->row_ptr[i + 1]; k++)
        {
            int row = A->col_idx[k];
            double a_val = A->values[k];
            for (j = B->row_ptr[row]; j < B->row_ptr[row + 1]; j++)
            {
                int col = B->col_idx[j];
                double b_val = B->values[j];
                C->values[col] += a_val * b_val;
            }
        }
    }
}

int main()
{
    // // 测试密集矩阵乘法
    // Matrix *A_dense = create_and_init_matrix(SIZE, SIZE, 0.0, 0);
    // Matrix *B_dense = create_and_init_matrix(SIZE, SIZE, 0.0, 0);
    // Matrix *C_dense = create_and_init_matrix(SIZE, SIZE, 0.0, 0);

    // clock_t start = clock();
    // manual_dgemm(A_dense, B_dense, C_dense);
    // clock_t end = clock();
    // double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time used by manual_dgemm: %lf seconds\n", cpu_time_used);

    // start = clock();
    // manual_dgemm2(A_dense, B_dense, C_dense);
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time used by manual_dgemm2: %lf seconds\n", cpu_time_used);

    // start = clock();
    // sparse_dgemm(A_dense, B_dense, C_dense);
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time used by sparse_dgemm: %lf seconds\n", cpu_time_used);

    // free_matrix(A_dense);
    // free_matrix(B_dense);
    // free_matrix(C_dense);

    // 测试稀疏矩阵乘法
    Matrix *A_sparse = create_and_init_matrix(SIZE, SIZE, 0.1, 1);
    Matrix *B_sparse = create_and_init_matrix(SIZE, SIZE, 0.1, 1);
    Matrix *C_sparse = create_and_init_matrix(SIZE, SIZE, 0.0, 1);

    clock_t start = clock();
    manual_dgemm(A_sparse, B_sparse, C_sparse);
    clock_t end = clock();
    clock_t cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm (sparse): %lf seconds\n", cpu_time_used);

    start = clock();
    manual_dgemm2(A_sparse, B_sparse, C_sparse);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by manual_dgemm2 (sparse): %lf seconds\n", cpu_time_used);

    start = clock();
    sparse_dgemm(A_sparse, B_sparse, C_sparse);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used by sparse_dgemm (sparse): %lf seconds\n", cpu_time_used);

    free_matrix(A_sparse);
    free_matrix(B_sparse);
    free_matrix(C_sparse);

    return 0;
}