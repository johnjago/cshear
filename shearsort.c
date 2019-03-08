#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "shearsort.h"
#include "swap.h"
#include "array_utils.h"
#include "shared.h"
#include "bubble.h"

void shearsort(void *arg)
{
  int index = *((int *) arg);
  free(arg);
  int col[n];
  int phase;

  for (phase = 1; phase <= log2(n*n) + 1; phase++) {
    if (phase % 2 != 0) {
      // sort the rows since it's an odd phase
      bubble_sort(mesh[index]);
      if (index % 2 != 0) {
        reverse(mesh[index], n);
      }
    } else {
      // sort the columns since it's an even phase
      extract_col((int **)mesh, index, col);
      bubble_sort(&col);
      insert_col((int **)mesh, index, col);
    }

    // wait for all threads to catch up before starting the next phase
    pthread_mutex_lock(&mutex);
    num_complete++;
    if (num_complete != n) {
      pthread_cond_wait(&cond[index], &mutex);
    } else {
      printf("\nAfter phase %d:\n\n", phase);
      print_2d_array((int **)mesh, n, n);
      int i;
      for (i = 0; i < n; i++) {
        pthread_cond_signal(&cond[i]);
      }
      num_complete = 0;
    }
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(0);
}
