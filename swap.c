/* swap.c: a function for swapping the contents of two integer pointers */

#include "swap.h"

/* Swaps the contents of the two integer pointers.
 *
 * @param *a: pointer to an integer to be swapped with *b
 * @param *b: pointer to an integer to be swapped with *a
 */
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
