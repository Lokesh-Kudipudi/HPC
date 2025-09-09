#include <stdio.h>
#define N 3

void matrix_mul(int A[][N], int X[], int Y[], int n)
{
  int i, k;
  for (i = 0; i < n; i++)
  {
    Y[i] = 0;
    for (k = 0; k < n; k++)
      Y[i] += A[i][k] * X[k];
  }
}

int main()
{
  int A[N][N], X[N], Y[N];

  // Ask user for input
  printf("Enter elements of matrix A (%dx%d):\n", N, N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      scanf("%d", &A[i][j]);
  printf("Enter elements of vector X (%d elements):\n", N);

  for (int i = 0; i < N; i++)
    scanf("%d", &X[i]);

  matrix_mul(A, X, Y, N);

  printf("Resultant Matrix Y:\n");
  for (int i = 0; i < N; i++)
    printf("%d ", Y[i]);
  printf("\n");
  return 0;
}