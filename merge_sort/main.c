#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

typedef enum
{
    INDEX,
    CNPJ,
    HEIGHT,
    PRIORITY

} SortedBy_t;

typedef struct
{
    char index[12];
    uint64_t cnpj;
    uint32_t height;
    uint8_t priority; // Smaller = More Priority
} Container_t;

bool validate_cnpj(uint64_t cnpj_1, uint64_t cnpj_2)
{
    if (cnpj_1 == cnpj_2)
        return true;
    return false;
}

Container_t *merge(Container_t *array_ptr, int start_pos, int middle, int end_pos, SortedBy_t sorted_by)
{
    // Left Array = start to middle
    // Rigth Array = middle + 1 (curr) to end

    const int subarr_len = end_pos - start_pos + 1;

    Container_t *sorted_subarr = (Container_t *)malloc(sizeof(Container_t) * subarr_len);

    int i = start_pos, j = middle + 1, k = 0;
    //uint32_t nl = middle - start_pos + 1; // Left  array len
    //uint32_t nr = end_pos - middle;       // Right array len

    while (i <= middle && j <= end_pos)
    {
        switch (sorted_by)
        {

        case INDEX:
            if (strcmp(array_ptr[i].index, array_ptr[j].index) < 0)
                sorted_subarr[k++] = array_ptr[i++];
            else
                sorted_subarr[k++] = array_ptr[j++];
            break;

        case CNPJ:
            if (array_ptr[i].cnpj < array_ptr[j].cnpj)
                sorted_subarr[k++] = array_ptr[i++];
            else
                sorted_subarr[k++] = array_ptr[j++];
            break;

        case HEIGHT:
            if (array_ptr[i].height < array_ptr[j].height)
                sorted_subarr[k++] = array_ptr[i++];
            else
                sorted_subarr[k++] = array_ptr[j++];
            break;

        case PRIORITY:
            if (array_ptr[i].priority < array_ptr[j].priority)
                sorted_subarr[k++] = array_ptr[i++];
            else
                sorted_subarr[k++] = array_ptr[j++];
            break;
        }
    }

    while (i <= middle)
        sorted_subarr[k++] = array_ptr[i++];

    while (j <= end_pos)
        sorted_subarr[k++] = array_ptr[j++];

    for (int i = start_pos, k = 0; i <= end_pos; i++, k++)
        array_ptr[i] = sorted_subarr[k];
}

void merge_sort(Container_t *array_ptr, int start_pos, int end_pos, SortedBy_t sorted_by)
{
    // Recursao
    if (start_pos < end_pos)
    {
        int middle = start_pos + (end_pos - start_pos) / 2;
        merge_sort(array_ptr, start_pos, middle, sorted_by);
        merge_sort(array_ptr, middle + 1, end_pos, sorted_by);

        merge(array_ptr, start_pos, middle, end_pos, sorted_by);
    }
    // Caso base - Vazio
}

Container_t *registered_ptr, *selected_ptr, *unsorted_registered_ptr;
int32_t registered_len, selected_len;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    // Allocating Registered Containers
    if (!fscanf(input_fp, "%d", &registered_len))
        printf("Não foi possivel fazer a leitura do arquivo\n");

    registered_ptr = malloc(registered_len * sizeof(Container_t));

    for (int i = 0; i < registered_len; i++)
    {
        char index[12];
        uint64_t cnpj;
        uint32_t height, c1, c2, c3, c4, c5;

        if (!fscanf(input_fp, "%s  %2d.%3d.%3d/%4d-%2d %d",
                    // Container index
                    index,
                    // Business CNPJ
                    &c1,
                    &c2,
                    &c3,
                    &c4,
                    &c5,
                    // Height
                    &height))
            printf("Não foi possivel fazer a leitura do arquivo\n");

        cnpj = c1 * pow(10, 12) + c2 * pow(10, 9) + c3 * pow(10, 6) + c4 * pow(10, 2) + c5;

        Container_t container = {
            .height = height,
            .cnpj = cnpj,
            .priority = 3 // default value (low priority)
        };

        strncpy(container.index, index, sizeof(container.index));

        registered_ptr[i] = container;
    }

    // Allocating Selected Containers
    if (!fscanf(input_fp, "%d", &selected_len))
        printf("Não foi possivel fazer a leitura do arquivo\n");

    selected_ptr = malloc(selected_len * sizeof(Container_t));

    for (int i = 0; i < selected_len; i++)
    {
        char index[12]; // n + end_of_string caratcher (00);
        uint64_t cnpj;
        uint32_t height, c1, c2, c3, c4, c5;

        if (!fscanf(input_fp, "%11s  %2d.%3d.%3d/%4d-%2d %d",
                    // Container index
                    index,
                    // Business CNPJ
                    &c1,
                    &c2,
                    &c3,
                    &c4,
                    &c5,
                    // Height
                    &height))
            printf("Não foi possivel fazer a leitura do arquivo\n");

        cnpj = c1 * pow(10, 12) + c2 * pow(10, 9) + c3 * pow(10, 6) + c4 * pow(10, 2) + c5;

        Container_t container = {
            .height = height,
            .cnpj = cnpj,
            .priority = 3 // default value (low priority)
        };

        strncpy(container.index, index, sizeof(container.index));

        selected_ptr[i] = container;
    }

    merge_sort(registered_ptr, 0, registered_len - 1, INDEX);
    merge_sort(selected_ptr, 0, selected_len - 1, INDEX);


}