#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    int32_t seg_len, arr_count;

    fscanf(input_fp, "%d %d", &arr_count, &seg_len);
    printf("%d %d\n", arr_count, seg_len);

    for (int i = 0; i < arr_count; i++)
    {
        uint32_t id, pkt_len;

        fscanf(input_fp, "%d %d", &id, &pkt_len);

        printf("%d %d ", id, pkt_len);

        for (int j = 0; j < pkt_len; j++)
        {
            int32_t byte;
            fscanf(input_fp, "%02X", &byte);
            printf("%02X ", byte);
        }
        printf("\n");
    }
}