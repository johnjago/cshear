#ifndef ARRAY_UTILS
#define ARRAY_UTILS

/* array_utils.h: functions for manipulating arrays */

void reverse(int arr[], int size);
void print_2d_array(int **arr, int num_rows, int num_cols);
void extract_col(int **arr, int col, int* buf);
void insert_col(int **arr, int col, int* buf);

#endif
