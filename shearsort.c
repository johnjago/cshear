#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "macros.h"
#include "shearsort.h"
#include "swap.h"
#include "array_utils.h"
#include "shared.h"

void shearsort(void *arg)
{
  int index = *((int *) arg);
  free(arg);
  int *arr;
  int col[n];
  int phase;

  for (phase = 1; phase <= log2(N) + 1; phase++) {
    if (phase % 2 != 0) {
      // row sort
      arr = mesh[index];
      int i, j;
      for (i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
          if (arr[j] > arr[j + 1]) {
            swap(&arr[j], &arr[j + 1]);
          }
        }
      }
      if (index % 2 != 0) {
        reverse(mesh[index], n);
      }
    } else {
      // column sort
      extract_col(mesh, index, col);
      int i, j;
      for (i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
          if (col[j] > col[j + 1]) {
            swap(&col[j], &col[j + 1]);
          }
        }
      }
      insert_col(mesh, index, col);
    }

    pthread_mutex_lock(&mutex);
    num_complete++;
   // printf("Phase: %d\nindex: %d\nIt looks like:\n", phase, index);
   // print_2d_array(mesh, n, n);
   // printf("Num complete: %d\n\n", num_complete);
    if (num_complete != n) {
      pthread_cond_wait(&cond[index], &mutex);
    } else {
      printf("\nAfter phase %d:\n\n", phase);
      print_2d_array(mesh, n, n);
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

