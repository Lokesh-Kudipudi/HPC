#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_mul(long **A, long *X, long *Y, int n)
{
#pragma omp parallel
  {
    int threadID = omp_get_thread_num();
    int numThreads = omp_get_num_threads();
    int offset = n / numThreads + (threadID < n % numThreads ? 1 : 0);
    int start = threadID * (n / numThreads) + (threadID < n % numThreads ? threadID : n % numThreads);
    int end = start + offset;
    printf(" Thread %d processing %d to %d ", threadID, start, end-1);
    for (int i = start; i < end; i++)
    {
      Y[i] = 0;
      for (int k = 0; k < n; k++)
        Y[i] += A[i][k] * X[k];
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s <N-Matrix Size>\n", argv[0]);
    return 1;
  }
  int N = atoi(argv[1]);
  long **A = malloc(N * sizeof(long*));
  long *X = malloc(N * sizeof(long));
  long *Y = malloc(N * sizeof(long));
  int numberA = 1;
  int numberX = 1;
  for (int i = 0; i < N; i++) {
    A[i] = malloc(N * sizeof(double));
    for (int j = 0; j < N; j++) {
      A[i][j] = numberA;
      numberA++;
    }
    X[i] = numberX;
    numberX++;
    Y[i] = 0;
  }
  printf("Matrix size: %dx%d\n", N, N);
  int max_threads; 
#pragma omp parallel
  {
  #pragma omp master
    {
      max_threads = omp_get_num_threads();
      printf("Number of threads: %d\n", max_threads);
    }
  }
  // Measure execution time using OpenMP wall clock
  double start_time = omp_get_wtime();
  matrix_mul(A, X, Y, N);
  double end_time = omp_get_wtime();
  double elapsed = end_time - start_time;

  printf("Resultant Matrix Y:\n");
  for (int i = 0; i < N; i++)
    printf("%ld ", Y[i]);
  printf("\n");
  printf("Execution time: %.6f seconds\n", elapsed);
  for (int i = 0; i < N; i++) free(A[i]);
  free(A);
  free(X);
  free(Y);
  return 0;
}