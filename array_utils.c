/* array_utils.c: functions for manipulating arrays
 */

#include <stdio.h>

#include "macros.h"
#include "array_utils.h"
#include "swap.h"

/* reverse(): reverse an array
 * @param arr[]
 * @param size:
 */
void reverse(int arr[], int size)
{
  int start = 0;
  int end = size - 1;
  while (start < end) {
    swap(&arr[start], &arr[end]);
    start++;
    end--;
  }
}

void print_2d_array(int arr[][4], int num_rows, int num_cols)
{
  int i, j;
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      printf("%3d", arr[i][j]);
    }
    printf("\n");
  }
}

void extract_col(int arr[][4], int col, int* buf)
{
  int i;
  for (i = 0; i < n; i++) {
    buf[i] = arr[i][col];
  }
}

void insert_col(int arr[][4], int col, int* buf)
{
  int i;
  for (i = 0; i < n; i++) {
    arr[i][col] = buf[i];
  }
}

