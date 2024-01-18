#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t swap_count, call_count;

void swap(int32_t *array_ptr, int source_pos, int dest_pos)
{
    swap_count++;

    int32_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

int32_t median(int a, int b, int c, int32_t n, int32_t lo)
{
    call_count++;

    if ((a >= b && a <= c) || (a <= b && a >= c))
        return lo + (n / 4); // a
    else if ((b >= a && b <= c) || (b <= a && b >= c))
        return lo + (n / 2); // b
    else
        return lo + (3 * n / 2); // c
}

int32_t lomuto_median(int32_t* vector, int32_t low, int32_t high)
{
  call_count++;
  
  int32_t n = high - low + 1;
  
  int32_t a = vector[low + (n / 4)], b = vector[low + (n / 2)], c = vector[low + (3 * n / 4)];

  int32_t k = median(a, b, c, n low);

  swap(vector, high, k)
  
  int32_t P = vector_ptr[high], x = low - 1, y = low;

    for (y = i; y < j; y++)
        if (vector_ptr[y] <= P)
            swap(vector_ptr, ++x, y);

    swap(vector_ptr, ++x, high);

    return x;
  
}
