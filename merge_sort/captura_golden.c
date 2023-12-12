#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

int32_t registered_len, selected_len;

typedef struct
{
    char index[12];
    uint64_t cnpj;
    uint32_t height;
    uint8_t priority; // Smaller = More Priority
} Container_t;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");

    // Registered Containers
    fscanf(input_fp, "%d", &registered_len);
    printf("%d\n", registered_len);

    for (int i = 0; i < registered_len; i++)
    {
        char index[12];
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

        printf("%s  %2d.%3d.%3d/%4d-%2d %u\n",
               // Container index
               index,
               // Business CNPJ
               c1,
               c2,
               c3,
               c4,
               c5,
               // Height
               height);
    }

    // Selected Containers
    fscanf(input_fp, "%d", &selected_len);
    printf("%d\n", selected_len);

    for (int i = 0; i < selected_len; i++)
    {
        char index[12];
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
               &height
        );

        printf("%s  %2d.%3d.%3d/%4d-%2d %d\n",
                // Container index
               index,
               // Business CNPJ
               c1,
               c2,
               c3,
               c4,
               c5,
               // Height
               height
        );
    }
}