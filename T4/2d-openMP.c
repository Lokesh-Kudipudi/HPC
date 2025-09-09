#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void matrix_mul(long **A, long *X, long *Y, int n)
{
  // Calculate grid dimensions for 2D partitioning
  int num_threads = omp_get_max_threads();
  int grid_size = (int)sqrt(num_threads);
  int block_size = n / grid_size + (n % grid_size != 0);

#pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int row_block = thread_id / grid_size;
    int col_block = thread_id % grid_size;

    // Calculate block boundaries
    int row_start = row_block * block_size;
    int row_end = (row_block + 1) * block_size;
    if (row_end > n)
      row_end = n;

    int col_start = col_block * block_size;
    int col_end = (col_block + 1) * block_size;
    if (col_end > n)
      col_end = n;

    // Process assigned block
    for (int i = row_start; i < row_end; i++)
    {
      long temp = 0;
      for (int k = col_start; k < col_end; k++)
      {
        temp += A[i][k] * X[k];
      }
#pragma omp atomic
      Y[i] += temp;
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <N-Matrix Size>\n", argv[0]);
    return 1;
  }
  int N = atoi(argv[1]);
  long **A = malloc(N * sizeof(long *));
  long *X = malloc(N * sizeof(long));
  long *Y = malloc(N * sizeof(long));
  int numberA = 1;
  int numberX = 1;
  for (int i = 0; i < N; i++)
  {
    A[i] = malloc(N * sizeof(double));
    for (int j = 0; j < N; j++)
    {
      A[i][j] = numberA;
      numberA++;
    }
    X[i] = numberX;
    numberX++;
    Y[i] = 0;
  }
  int max_threads;
  // Measure execution time using OpenMP wall clock
  double start_time = omp_get_wtime();
  matrix_mul(A, X, Y, N);
  double end_time = omp_get_wtime();
  double elapsed = end_time - start_time;

  printf("Execution time: %.8f seconds for size %d\n", elapsed, N);
  for (int i = 0; i < N; i++)
    free(A[i]);
  free(A);
  free(X);
  free(Y);
  return 0;
}