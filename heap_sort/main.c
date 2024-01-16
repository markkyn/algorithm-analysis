#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

void heapify_min(int32_t *V, uint32_t n, uint32_t i)
{
    uint32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL] < V[iP])
        iP = iL;

    if (iR < n && V[iR] < V[iP])
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_min(V, n, iP);
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

void insert_max(int32_t *heap, uint32_t *heap_len, uint8_t byte)
{
    heap[*heap_len] = byte;

    // heapify_max(heap, *heap_len, 0);

    (*heap_len)++;
};

void insert_min(int32_t *heap, uint32_t heap_len, uint8_t byte)
{
    heap[heap_len] = byte;

    heapify_min(heap, heap_len, 0);
}

int32_t smallest(int32_t *heap, uint32_t heap_len)
{
    // return smallest index
}

void build_heap(int32_t *V, uint32_t n)
{
    int32_t iP = parent(n - 1);

    while (iP >= 0)
    {
        uint32_t iL = left(iP), iR = right(iP);

        heapify_max(V, n, iP);
        heapify_max(V, n, iL);
        heapify_max(V, n, iR);

        iP--;
    }
}

void heap_sort_max(int32_t *V, int32_t n)
{
    build_heap(V, n);

    for (int32_t i = n - 1; i > 0; i--)
    {
        swap(V, 0, i);

        heapify_max(V, i, 0);
    }
}

void heap_sort_min(int32_t *V, int32_t n)
{
    build_heap(V, n);

    for (int32_t i = n - 1; i > 0; i--)
    {
        swap(V, 0, i);

        heapify_min(V, i, 0);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    int n_total, seg_len;

    int32_t *heap = malloc(512 * sizeof(uint8_t));
    uint32_t heap_len = 0;

    uint32_t next = 0; // next to be processed

    fscanf(input_fp, "%d %d", &n_total, &seg_len);
    // Iteração Geral
    for (int i = 0; i < n_total; i += seg_len)
    {
        // Iteração pelo Segmento
        for (int32_t j = 0; j < seg_len; j++)
        {
            int id, len_packet;
            fscanf(input_fp, "%d %d", &id, &len_packet);

            uint32_t byte;

            // Iteração pelo Pacote
            printf("Leitura:\n\t");
            for (int k = 0; k < len_packet; k++)
            {
                fscanf(input_fp, "%X", &byte);
                // insert_max(heap, &heap_len, byte);
                printf("%X ", byte);
            }

            heap_sort_max(heap, heap_len);

            printf
            for()

            int x = 0;
            while (smallest(heap, heap_len) == next)
            {
                printf()

                next++;
            }
            printf("\n");
        }
    }
}