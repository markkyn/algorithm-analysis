/* Quicksort with haore partition */

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

int32_t haore(int32_t *vector, int32_t i, int32_t j) // i = first position ; j = last position
{

    // Arbitrary Pivot.
    int32_t P = vector[i], x = i - 1, y = j + 1;

    while (true)
    {
        while (vector[--y] > P)
            ;
        while (vector[++x] < P)
            ;
        if (x < y)
            swap(vector, x, y);
        else {
            printf("%d\n", y);
            return y; // Duvida: existe algum motivo pelo retorno do y e nao do x

         }

    }
}

void recursive_quicksort(int32_t *vector, uint32_t start, uint32_t end)
{

    if (start < end)
    {
        int32_t pivot = haore(vector, start, end);
        // sorting by partitioning;

        recursive_quicksort(vector, start, pivot - 1);
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

        printf("oi\n");
        recursive_quicksort(vector_ptr, 0, vector_len-1);

        for (int j = 0; j < vector_len; j++)
            fprintf(output_fp, "%d ", vector_ptr[j]);

        fprintf(output_fp, "\n");
        free(vector_ptr);
    }
}