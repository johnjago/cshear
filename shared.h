#ifndef SHARED
#define SHARED

extern int mesh[n][n];
extern int num_complete;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond[n];

#endif
