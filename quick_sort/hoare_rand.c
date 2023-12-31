/* Quicksort with hoare partition */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int32_t *array_ptr, int source_pos, int dest_pos)
{
    int32_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

int32_t hoare(int32_t *vector, int32_t low, int32_t high) // i = first position ; j = last position
{
    // Arbitrary Pivot.
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

int32_t hoare_rand(int32_t *vector, int32_t i, int32_t j)
{

    swap(vector, i, (i + abs(i) % (j - i + 1)));

    return hoare(vector, i, j);
}

void recursive_quicksort(int32_t *vector, int32_t start, int32_t end)
{

    if (start < end)
    {
        int32_t pivot = hoare_rand(vector, start, end);
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

        recursive_quicksort(vector_ptr, 0, vector_len - 1);

        for (int j = 0; j < vector_len; j++)
        {
            fprintf(output_fp, "%d ", vector_ptr[j]);
        }
        fprintf(output_fp, "\n");
        free(vector_ptr);
    }
}