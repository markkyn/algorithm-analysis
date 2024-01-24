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

    if ((a >= b && a <= c) || (a <= b && a >= c))
        return lo + (n / 4); // a
    else if ((b >= a && b <= c) || (b <= a && b >= c))
        return lo + (n / 2); // b
    else
        return lo + (3 * n / 2); // c
}

int32_t lomuto_median(int32_t *vector, int32_t low, int32_t high)
{
    call_count++;

    int32_t n = high - low + 1;

    int32_t a = vector[low + (n / 4)], b = vector[low + (n / 2)], c = vector[low + (3 * n / 4)];

    int32_t k = median(a, b, c, n, low);

    swap(vector, high, k);

    int32_t P = vector[high], x = low - 1, y = low;

    for (y = low; y < high; y++)
        if (vector[y] <= P)
            swap(vector, ++x, y);

    swap(vector, ++x, high);

    return y;
}

void recursive_quicksort(int32_t *vector, int32_t start, int32_t end)
{
    if (start < end)
    {
        int32_t pivot = lomuto_median(vector, start, end);
        // sorting by partitioning;

        recursive_quicksort(vector, start, pivot-1);
        recursive_quicksort(vector, pivot + 1, end);
    }
    return; // useless return (end recursion);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    int32_t vectors_count, vector_len;

    fscanf(input_fp, "%d", &vectors_count);
    for (int i = 0; i < vectors_count; i++)
    {
        fscanf(input_fp, "%d", &vector_len);

        int32_t *vector_ptr = malloc(vector_len * sizeof(int32_t));

        for (int j = 0; j < vector_len; j++)
            fscanf(input_fp, "%d", &vector_ptr[j]);

        recursive_quicksort(vector_ptr, 0, vector_len - 1);
    printf("\nAqui\n");

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