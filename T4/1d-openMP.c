#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_mul(int **A, int *X, int *Y, int n)
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
    printf("Usage: %s <N>\n", argv[0]);
    return 1;
  }
  int N = atoi(argv[1]);
  int num_threads = atoi(argv[2]);
  int **A = malloc(N * sizeof(int*));
  int *X = malloc(N * sizeof(int));
  int *Y = malloc(N * sizeof(int));
  int numberA = 1;
  int numberX = 1;
  for (int i = 0; i < N; i++) {
    A[i] = malloc(N * sizeof(int));
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
#pragma omp num_threads(num_threads)
  matrix_mul(A, X, Y, N);
  printf("Resultant Matrix Y:\n");
  for (int i = 0; i < N; i++)
    printf("%d ", Y[i]);
  printf("\n");
  for (int i = 0; i < N; i++) free(A[i]);
  free(A);
  free(X);
  free(Y);
  return 0;
}