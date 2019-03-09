/* bubble.c: a function to perform bubble sort */

#include "bubble.h"
#include "shared.h"
#include "swap.h"

/* Performs an in place bubble sort on an array.
 *
 * @param *array: the array to be sorted
 */
void bubble_sort(void *array)
{
  int *arr = array;
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for(j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}
