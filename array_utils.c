/* array_utils.c: functions for manipulating arrays
 */

#include <stdio.h>

#include "array_utils.h"
#include "swap.h"
#include "shared.h"

/* Reverses an array in place.
 *
 * @param arr[]: the array to be reversed
 * @param size: the length of the array
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

/* Prints a two dimensional array to standard output.
 *
 * @param arr[][n]: the array to be printed
 * @param num_rows: the number of rows in the array
 * @param num_cols: the number of columns in the array
 */
void print_2d_array(int **arr, int num_rows, int num_cols)
{
  int i, j;
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      printf("%3d", arr[i][j]);
    }
    printf("\n");
  }
}

/* Takes the column at index col and copies it into buf.
 *
 * @param arr[][n]: the array from which a column will be copied
 * @param col: the column to copy
 * @param buf: the location to store the column
 */
void extract_col(int **arr, int col, int* buf)
{
  int i;
  for (i = 0; i < n; i++) {
    buf[i] = arr[i][col];
  }
}

/* Inserts the array in buf as a column in the two dimensional array
 * at index col.
 *
 * @param arr[][n]: the array to insert the column into
 * @param col: the index where the insertion should occur
 * @param buf: the buffer that contains the elements to be inserted
 */
void insert_col(int **arr, int col, int* buf)
{
  int i;
  for (i = 0; i < n; i++) {
    arr[i][col] = buf[i];
  }
}
