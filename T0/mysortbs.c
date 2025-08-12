#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000 // 1 million elements

// Swap two elements
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Bubble Sort implementation
void bubbleSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    // Flag to optimize bubble sort by detecting if any swap occurred
    int swapped = 0;

    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(&arr[j], &arr[j + 1]);
        swapped = 1;
      }
    }

    // If no swapping occurred, array is already sorted
    if (swapped == 0)
      break;
  }
}

int main()
{
  int *arr = (int *)malloc(SIZE * sizeof(int));
  if (!arr)
  {
    printf("Memory allocation failed\n");
    return 1;
  }

  srand(time(NULL));

  // Fill array with random integers
  for (int i = 0; i < SIZE; i++)
  {
    arr[i] = rand();
  }

  // Measure execution time
  clock_t start, end;
  start = clock();

  bubbleSort(arr, SIZE);

  end = clock();
  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("BubbleSort of %d elements took %.2f seconds.\n", SIZE, time_taken);

  free(arr);
  return 0;
}