/* main.c: read input and create threads to perform shearsort */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "shared.h"
#include "shearsort.h"
#include "array_utils.h"

int n;
int **mesh;
int num_complete = 0;
const char *FILENAME = "input.txt";
pthread_mutex_t mutex;
pthread_cond_t *cond;

int main()
{
  FILE *fp;
  int buff[1024];
  int i, j;
  int nrows = 0;
  int ncols = 0;
  int count = 0;
  pthread_t *threads;

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    printf("Error opening file.\n");
    exit(EXIT_FAILURE);
  }

  /* count the number of rows */
  char line[1024];
  while(fgets(line, 1024, fp)) {
    nrows++;
  }
  
  rewind(fp);
 
  /* If the number of integers in any row is not equal to the number
   * of rows, we cannot continue.
   */
  while(fgets(line, 1024, fp)) {
    ncols = 0;
    int offset;
    char *lineptr = &line[0];
    while (sscanf(lineptr, "%d%n", &buff[count], &offset) == 1) {
      ncols++;
      count++;
      lineptr += offset;
    }
    if (nrows != ncols) {
      fprintf(stderr, "Input file does not contain a square array.\n");
      exit(EXIT_FAILURE);
    }
  }

  /* we have an n x n matrix */
  n = nrows;

  /* allocate space now that we know n */
  mesh = (int **)malloc(n * sizeof(int*));
  for (i = 0; i < n; i++) {
    mesh[i] = (int *)malloc(n * sizeof(int));
  }
  cond = (pthread_cond_t *)malloc(n * sizeof(pthread_cond_t));
  threads = (pthread_t *)malloc(n * sizeof(pthread_t));

  /* insert the integers into the mesh */
  count = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      mesh[i][j] = buff[count];
      count++;
    }
  }

  printf("Initially:\n\n");
  print_2d_array((int **)mesh, n, n);

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
