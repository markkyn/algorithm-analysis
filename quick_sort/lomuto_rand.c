#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int32_t *array_ptr, int source_pos, int dest_pos)
{
    int32_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

int32_t lomuto_partition(int32_t *vector_ptr, int32_t i, int32_t j)
{
    int32_t P = vector_ptr[j], x = i - 1, y = i;

    for (y = i; y < j; y++)
        if (vector_ptr[y] <= P)
            swap(vector_ptr, ++x, y);

    swap(vector_ptr, ++x, j);

    return x;
}

int32_t lomuto_rand(int32_t *vector, int32_t i, int32_t j)
{
    swap(vector, j, (i + abs(i) % (j - i + 1) ));

    return lomuto_partition(vector, i, j);

}

void recursive_quicksort(int32_t *vector_ptr, int32_t low, int32_t high)
{
    if (low < high)
    {
        int32_t pivot = lomuto_rand(vector_ptr, low, high);

        recursive_quicksort(vector_ptr, low, pivot - 1);
        recursive_quicksort(vector_ptr, pivot + 1, high);
    }
}

uint32_t *vector_ptr, vector_count, vector_len;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    fscanf(input_fp, "%d", &vector_count);

    // Iteration over unsorted vectors
    for (int i = 0; i < vector_count; i++)
    {
        fscanf(input_fp, "%d", &vector_len);

        // Vector Allocation
        vector_ptr = malloc(vector_len * sizeof(uint32_t));

        // Vector Population
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