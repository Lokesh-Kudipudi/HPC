#include <stdio.h>
#include <omp.h>
#define N 10

void matrix_mul(int A[][N], int X[], int Y[], int n)
{

#pragma omp parallel
  {
    int threadID = omp_get_thread_num();
    int numThreads = omp_get_num_threads();
    int offset = n / numThreads; // Ceiling division
    for (int i = threadID * offset; i < threadID * offset + offset; i++)
    {
      Y[i] = 0;
      for (int k = 0; k < n; k++)
        Y[i] += A[i][k] * X[k];
    }
  }
}

int main()
{
  int A[N][N], X[N], Y[N];
  int numberA = 0;
  int numberX = 1;

  // Initialize matrices with some values instead of user input
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      A[i][j] = numberA; // Simple initialization pattern
      numberA++;
    }
    X[i] = numberX; // Initialize vector X
    numberX++;
    Y[i] = 0; // Initialize result vector Y
  }

  printf("Matrix size: %dx%d\n", N, N);

  // Get number of available threads
  int max_threads;
#pragma omp parallel
  {
#pragma omp master
    {
      max_threads = omp_get_num_threads();
      printf("Number of threads: %d\n", max_threads);
    }
  }

#pragma omp num_threads(2)
  matrix_mul(A, X, Y, N);

  printf("Resultant Matrix Y:\n");
  for (int i = 0; i < N; i++)
    printf("%d ", Y[i]);
  printf("\n");
  return 0;
}