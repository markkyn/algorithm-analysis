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

void swap(Container_t *array_ptr, int source_pos, int dest_pos)
{
    // printf("Swapping %d <-> %d\n", source_pos, dest_pos);
    Container_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

void merge(Container_t *array_ptr, int start_pos, int middle, int end_pos, SortedBy_t sorted_by)
{
    for (int i = start_pos; i < end_pos; i++)
    {
        int curr = i;
        for (int j = middle; j <= end_pos; j++)
        {
            switch (sorted_by)
            {
            case INDEX:
                if (strcmp(array_ptr[j].index, array_ptr[curr].index) < 0)
                {
                    swap(array_ptr, curr, j);
                    curr = j;
                }
                break;

            case CNPJ:
                if (array_ptr[j].cnpj < array_ptr[curr].cnpj)
                {
                    swap(array_ptr, curr, j);
                    curr = j;
                }
                break;

            case HEIGHT:
                if (array_ptr[j].height < array_ptr[curr].height)
                {
                    swap(array_ptr, curr, j);
                    curr = j;
                }
            case PRIORITY:
                if (array_ptr[j].priority < array_ptr[curr].priority)
                {
                    swap(array_ptr, curr, j);
                    curr = j;
                }

            default:
                break;
            }
        }
    }
}

void merge_sort(Container_t *array_ptr, int start_pos, int end_pos, SortedBy_t sorted_by)
{
    if (start_pos < end_pos)
    {
        int middle = (start_pos + end_pos) / 2;
        merge_sort(array_ptr, start_pos, middle, sorted_by);
        merge_sort(array_ptr, middle + 1, end_pos, sorted_by);

        merge(array_ptr, start_pos, middle + 1, end_pos, sorted_by);
    }
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

    // Registered Containers
    fscanf(input_fp, "%d", &registered_len);
    registered_ptr = malloc(registered_len * sizeof(Container_t));
    unsorted_registered_ptr = malloc(registered_len * sizeof(Container_t));

    for (int i = 0; i < registered_len; i++)
    {
        char index[12];
        uint64_t cnpj;
        uint32_t height, c1, c2, c3, c4, c5;

        fscanf(input_fp, "%s  %2d.%3d.%3d/%4d-%2d %d",
               // Container index
               index,
               // Business CNPJ
               &c1,
               &c2,
               &c3,
               &c4,
               &c5,
               // Height
               &height);

        cnpj = c1 * pow(10, 12) + c2 * pow(10, 9) + c3 * pow(10, 6) + c4 * pow(10, 2) + c5;

        Container_t container = {
            .height = height,
            .cnpj = cnpj,
            .priority = 3 // default value (low priority)
        };

        strncpy(container.index, index, sizeof(container.index));

        registered_ptr[i] = container;
        unsorted_registered_ptr[i] = container;
    }

    // Selected Containers
    fscanf(input_fp, "%d", &selected_len);
    selected_ptr = malloc(selected_len * sizeof(Container_t));

    for (int i = 0; i < selected_len; i++)
    {
        char index[12]; // n + end_of_string caratcher (00);
        uint64_t cnpj;
        uint32_t height, c1, c2, c3, c4, c5;

        fscanf(input_fp, "%11s  %2d.%3d.%3d/%4d-%2d %d",
               // Container index
               index,
               // Business CNPJ
               &c1,
               &c2,
               &c3,
               &c4,
               &c5,
               // Height
               &height);

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

    for (int i = 0; i < registered_len; i++)
        printf("%s - %d\n", registered_ptr[i].index, registered_ptr[i].priority);

    // Priority Definition
    // TODO: Provavelmente Optimizável: O(n²)
    int last = 0;
    for (int i = 0; i < selected_len; i++)
    {
        for (int j = last; j < registered_len; j++)
        {
            if (strcmp(selected_ptr[i].index, registered_ptr[j].index) == 0)
            {

                double diff = (abs((float)registered_ptr[j].height - (float)selected_ptr[i].height) / (float)registered_ptr[j].height) * 100;

                printf("Container %c = %d - Container %c = %d - diff = %f\n",
                       registered_ptr[j].index[0], registered_ptr[j].height,
                       selected_ptr[i].index[0], selected_ptr[i].height,
                       diff);

                // Validations
                if (!validate_cnpj(selected_ptr[i].cnpj, registered_ptr[j].cnpj))
                {
                    selected_ptr[i].priority = 1;
                    registered_ptr[j].priority = 1;
                }
                else if (diff > 10)
                {
                    selected_ptr[i].priority = 2;
                    registered_ptr[j].priority = 2;
                }

                last = j;
                j = registered_len; // stop j-loop iteration
            }
        }
    }

    // Set Priority to Unsorted Registered Array
    for (int i = 0; i < registered_len; i++)
    {
        for (int j = 0; j < registered_len; j++)
        {
            if (strcmp(unsorted_registered_ptr[i].index, registered_ptr[j].index) == 0)
            {
                unsorted_registered_ptr[i].priority = registered_ptr[j].priority;
            }
        }
    }

    merge_sort(unsorted_registered_ptr, 0, registered_len - 1, PRIORITY);

    // File Printing Priority Sorted Array
    for (int i = 0; i < registered_len; i++)
    {
        printf("%s - %d\n", unsorted_registered_ptr[i].index, unsorted_registered_ptr[i].priority);
        for (int j = 0; j < selected_len; j++)
        {
            if (strcmp(unsorted_registered_ptr[i].index, selected_ptr[j].index) == 0)
            {
                if (unsorted_registered_ptr[i].priority == 1)
                    fprintf(output_fp,"%s: %ld<->%ld\n",
                            unsorted_registered_ptr[i].index,
                            unsorted_registered_ptr[i].cnpj, selected_ptr[j].cnpj
                    );
                else if (unsorted_registered_ptr[i].priority == 2)
                    fprintf(output_fp, "%s: %dkg (%d%%)\n",
                            unsorted_registered_ptr[i].index,
                            abs(unsorted_registered_ptr[i].height - selected_ptr[j].height),
                            (int)ceil( 
                                (float)  ( abs(unsorted_registered_ptr[i].height - selected_ptr[j].height) )
                                /        ( unsorted_registered_ptr[i].height * 0.01)
                            )
                    );
            }
        }
    }
}