#ifndef SHARED
#define SHARED

#include <pthread.h>

extern int n;
extern int **mesh;
extern int num_complete;
extern pthread_mutex_t mutex;
extern pthread_cond_t *cond;

#endif
