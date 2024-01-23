#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int32_t *V, int32_t i, int32_t j)
{
    int32_t t = V[i];

    V[i] = V[j];

    V[j] = t;
}

int32_t left(int32_t i)
{
    return (2 * i) + 1;
}

int32_t right(int32_t i)
{
    return (2 * i) + 2;
}

int32_t parent(int32_t i)
{
    if (i <= 0)
        return -1;

    return (i - 1) / 2;
}

void heapify_min(int32_t *V, int32_t n, int32_t i)
{
    int32_t iP = i, iL = left(i), iR = right(i);

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

void heapify_max(int32_t *V, int32_t n, int32_t i)
{
    // Heapfy Max downwards

    // V = vector
    // n = vector len
    // i = current index

    int32_t iP = i, iL = left(i), iR = right(i);

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

void heapify_max_upwards(int32_t *V, int32_t n, int32_t i)
{
    // Heapify Max Upwards

    if (i < 0)
        return;

    int32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL] > V[iP])
        iP = iL;

    if (iR < n && V[iR] > V[iP])
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_max_upwards(V, n, parent(i));
    }
}

void insert(int32_t *heap, int32_t *heap_len, uint8_t byte)
{
    heap[*heap_len] = byte;
    (*heap_len)++;
}

void insert_max(int32_t *heap, int32_t *heap_len, uint8_t byte)
{
    heap[*heap_len] = byte;
    (*heap_len)++;

    printf("\theap_len= %d\tparent = %d\n", (*heap_len), parent(*heap_len));
    heapify_max_upwards(heap, *heap_len, parent((*heap_len) - 1));
    printf("\t%X Inserido\n", byte);
};

void insert_min(int32_t *heap, int32_t heap_len, uint8_t byte)
{
    heap[heap_len] = byte;

    heapify_min(heap, heap_len, 0);
}


void build_heap(int32_t *V, int32_t n)
{
    int32_t iP = parent(n - 1);

    while (iP >= 0)
    {
        int32_t iL = left(iP), iR = right(iP);

        heapify_max(V, n, iP);
        heapify_max(V, n, iL);
        heapify_max(V, n, iR);

        iP--;
    }
}

void build_heap_min(int32_t *V, int32_t n)
{
    int32_t iP = parent(n - 1);

    while (iP >= 0)
    {
        int32_t iL = left(iP), iR = right(iP);

        heapify_min(V, n, iP);
        heapify_min(V, n, iL);
        heapify_min(V, n, iR);

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
    build_heap_min(V, n);

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

    int32_t *heap = malloc(15000 * 512 * sizeof(uint8_t));
    int32_t heap_len = 0;

    // next to be processed and process index
    int32_t next = 1, l = 0; 

    fscanf(input_fp, "%d %d", &n_total, &seg_len);
    // Iteração Geral
    for (int i = 0; i < n_total; i += seg_len)
    {
        // Iteração pelo Segmento
        for (int32_t j = 0; j < seg_len; j++)
        {
            int id, len_packet;
            fscanf(input_fp, "%d %d", &id, &len_packet);

            int32_t byte;

            // Iteração pelo Pacote
            for (int k = 0; k < len_packet; k++)
            {
                fscanf(input_fp, "%X", &byte);
                //printf("Inserção de: %X\n", byte);
                insert(heap, &heap_len, byte);
            }
        }

        heap_sort_max(heap, heap_len);

        fprintf(output_fp, "%d: ", i / seg_len);
        while (heap[l] == next)
        {
            fprintf(output_fp, "%02X ", heap[l]);

            next++;
            l++;
        }
        fprintf(output_fp, "\n");
    }
}