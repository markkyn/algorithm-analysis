#include <stdint.h>
#include <stdio.h>

void lomuto_partition(uint32_t *vector_ptr, int pivot_pos)
{
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
        for(int j = 0; j < vector_len; j++)
            fscanf(input_fp, "%d", &vector_ptr[j]);

        lomuto_partition(vector_ptr, vector_len - 1);

    }
}