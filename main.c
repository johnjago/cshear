#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "macros.h"
#include "array_utils.h"
#include "shearsort.h"
#include "shared.h"

int mesh[n][n];
int num_complete = 0;
pthread_mutex_t mutex;
pthread_cond_t cond[n];

int main()
{
  FILE *fp;
  char buff[255];
  int i, j;
  int tmp;
  pthread_t threads[n];

  fp = fopen(FILENAME, "r");
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      fscanf(fp, "%s", buff);
      sscanf(buff, "%d", &tmp);
      mesh[i][j] = tmp;
    }
  }
  
  printf("Initially:\n\n");
  print_2d_array(mesh, n, n);

  for (i = 0; i < n; i++) {
    int *arg = malloc(sizeof(*arg));
    if (arg == NULL) {
      fprintf(stderr, "Couldn't allocate memory for thread arg\n");
      exit(EXIT_FAILURE);
    }
    *arg = i;
    pthread_create(&threads[i], NULL, (void *)&shearsort, arg);
  }

  for (i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

