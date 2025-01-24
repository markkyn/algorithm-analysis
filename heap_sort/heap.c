#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int32_t order;
    int32_t *data_ptr;
    int32_t  data_len;

} Packet;


void swap(int32_t *V, uint32_t i, uint32_t j)
{
    int32_t t = V[i];

    V[i] = V[j];

    V[j] = t;
}

uint32_t left(uint32_t i)
{
    return (2 * i) + 1;
}

uint32_t right(uint32_t i)
{
    return (2 * i) + 2;
}

uint32_t parent(uint32_t i)
{
    return (i - 1) / 2;
}

void heapify(int32_t *V, uint32_t n, uint32_t i)
{
    // V = vector
    // n = vector len
    // i = current index

    uint32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL] < V[iP])
        iP = iL;

    if (iR < n && V[iR] < V[iP])
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify(V, n, iP);
    }
}

void heapify_max(int32_t *V, uint32_t n, uint32_t i)
{
    // V = vector
    // n = vector len
    // i = current index

    uint32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL] > V[iP])
        iP = iL;

    if (iR < n && V[iR] > V[iP])
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_max(V, n, iP);
    }
}

void build_heap(int32_t *V, uint32_t n)
{
    int32_t iP = parent(n - 1);

    while (iP >= 0)
    {
        uint32_t iL = left(iP), iR = right(iP);
        printf("iP: %d\tn:%d\n", iP, n);

        heapify_max(V, n, iP);
        heapify_max(V, n, iL);
        heapify_max(V, n, iR);

        iP--;
    }

    printf("Heap Maximo: \n\t");
    for (int i = 0; i < n; i++)
    {
        printf("%x ", V[i]);
    }
    printf("\n");
}

void heap_sort(int32_t *V, int32_t n)
{
    build_heap(V, n);

    for (int32_t i = n - 1; i > 0; i--)
    {
        swap(V, 0, i);

        heapify_max(V, i, 0);

        for (int i = 0; i < n; i++)
        {
            printf("%x ", V[i]);
        }
        printf("\n");
    }
}

uint32_t n_total;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    fscanf(input_fp, "%d", &n_total);
    int len_array;
    for (int i = 0; i < n_total; i++)
    {
        fscanf(input_fp, "%d", &len_array);
        int32_t *array = (int32_t *)malloc(sizeof(int32_t) * len_array);

        for (int j = 0; j < len_array; j++)
        {
            fscanf(input_fp, "%x", &array[j]);
        }
        printf("Heap Sort sobre: \n");
        for (int j = 0; j < len_array; j++)
            printf("%x ", array[j]);
        printf("\n");

        heap_sort(array, len_array);

        printf("Array Sortido: ");
        for (int j = 0; j < len_array; j++)
            printf("%x ", array[j]);
        printf("\n");
    }
}
