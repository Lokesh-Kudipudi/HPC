#include <stdio.h>
#include <stdlib.h>
// For timing
#include <time.h>

void matrix_mul(long **A, long *X, long *Y, int n)
{
  for (int i = 0; i < n; i++) {
    Y[i] = 0.0;
    for (int k = 0; k < n; k++)
      Y[i] += A[i][k] * X[k];
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
  for (int i = 0; i < N; i++) {
    A[i] = malloc(N * sizeof(long));
  }

  // Ask user for input
  // Autofill elements of matrix A and vector X with natural numbers
  int numberA = 1;
  int numberX = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = numberA;
      numberA++;
    }
    X[i] = numberX;
    numberX++;
  }
  printf("Matrix A and vector X autofilled with natural numbers.\n");

  matrix_mul(A, X, Y, N);

  printf("Resultant Matrix Y:\n");
  for (int i = 0; i < N; i++)
    printf("%ld ", Y[i]);
        // Start timing
        clock_t start = clock();
        matrix_mul(A, X, Y, N);
        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  for (int i = 0; i < N; i++) free(A[i]);
  free(A);
  free(X);
  free(Y);
  printf("\nExecution time: %.6f seconds\n", elapsed);
  return 0;
}