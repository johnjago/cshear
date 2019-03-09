/* shearsort.c
 *
 * Each thread runs this function concurrently to sort a certain
 * row or column of the matrix for log2(N) + 1 phases, where N is
 * the number of integers in the matrix.
 */

#include "shearsort.h"
#include "shared.h"
#include "bubble.h"
#include "swap.h"
#include "array_utils.h"

/* Sort the row or column index given by the reference *arg. Upon completeing
 * a row or column, the thread waits until all other threads have performed
 * their sorting for the phase before beginning the next phase.
 *
 * @param *arg: pointer to an integer which represents the index that the
 *              calling thread should sort
 */
void shearsort(void *arg)
{
  int index = *((int *) arg);
  free(arg);
  int col[n];
  int phase;
  int i;

  for (phase = 0; phase < log2(n*n) + 1; phase++) {
    if (phase % 2 != 0) {
      /* sort the rows since it's an odd phase */
      bubble_sort(mesh[index]);
      if (index % 2 != 0) {
        reverse(mesh[index], n);
      }
    } else {
      /* sort the columns since it's an even phase */
      extract_col((int **)mesh, index, col);
      bubble_sort(&col);
      insert_col((int **)mesh, index, col);
    }

    /* wait for all threads to catch up before starting the next phase */
    pthread_mutex_lock(&mutex);
    num_complete++;
    if (num_complete != n) {
      pthread_cond_wait(&cond[index], &mutex);
    } else {
      printf("\nAfter phase %d:\n\n", phase + 1);
      print_2d_array((int **)mesh, n, n);
      for (i = 0; i < n; i++) {
        pthread_cond_signal(&cond[i]);
      }
      num_complete = 0;
    }
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
}
