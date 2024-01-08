/* Quicksort with haore partition */

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

int32_t haore_median(int32_t *vector, int32_t low, int32_t high) // i = first position ; j = last position
{
    call_count++;

    int32_t n = high - low + 1;

    int32_t a = vector[low + (n / 4)], b = vector[low + (n / 2)], c = vector[low + (3 * n / 4)];

    int32_t k = median(a, b, c, n, low);

    swap(vector, low, k);

    // Median-of-three Pivot.
    int32_t P = vector[low], x = low - 1, y = high + 1;

    while (true)
    {
        while (vector[--y] > P)
            ;
        while (vector[++x] < P)
            ;
        if (x < y)
            swap(vector, x, y);
        else
            return y;
    }
}

void recursive_quicksort(int32_t *vector, int32_t start, int32_t end)
{
    if (start < end)
    {
        int32_t pivot = haore_median(vector, start, end);
        // sorting by partitioning;

        recursive_quicksort(vector, start, pivot);
        recursive_quicksort(vector, pivot + 1, end);
    }
    return; // useless return (end recursion);
}

int32_t *vector_ptr, vector_len, vectors_count;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    fscanf(input_fp, "%d", &vectors_count);

    for (int i = 0; i < vectors_count; i++)
    {
        fscanf(input_fp, "%d", &vector_len);

        vector_ptr = malloc(vector_len * sizeof(int32_t));

        for (int j = 0; j < vector_len; j++)
            fscanf(input_fp, "%d", &vector_ptr[j]);
        
        call_count++;
        recursive_quicksort(vector_ptr, 0, vector_len - 1);

        fprintf(output_fp, "Swap count = %d \tCall count = %d\n", swap_count, call_count);

        for (int j = 0; j < vector_len; j++)
        {
            fprintf(output_fp, "%d ", vector_ptr[j]);
        }
        fprintf(output_fp, "\n");

        swap_count = 0;
        call_count = 0;

        free(vector_ptr);
    }
}