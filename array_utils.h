#ifndef ARRAY_UTILS
#define ARRAY_UTILS

void reverse(int arr[], int size);
void print_2d_array(int arr[][4], int num_rows, int num_cols);
void extract_col(int arr[][4], int col, int* buf);
void insert_col(int arr[][4], int col, int* buf);

#endif
