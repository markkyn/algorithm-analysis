#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int32_t id;
    int32_t *data;
    int32_t data_len;
} Packet_t;

void swap(Packet_t *V, int32_t i, int32_t j)
{
    Packet_t t = V[i];

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

void heapify_min(Packet_t *V, int32_t n, int32_t i)
{
    int32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL].id < V[iP].id)
        iP = iL;

    if (iR < n && V[iR].id < V[iP].id)
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_min(V, n, iP);
    }
}

void heapify_min_upwards(Packet_t *V, int32_t n, int32_t i)
{
    // Heapify min Upwards

    if (i < 0)
        return;

    int32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL].id < V[iP].id)
        iP = iL;

    if (iR < n && V[iR].id < V[iP].id)
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_min_upwards(V, n, parent(i));
    }
}

void heapify_max(Packet_t *V, int32_t n, int32_t i)
{
    // Heapfy Max downwards

    // V = vector
    // n = vector len
    // i = current index

    int32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL].id > V[iP].id)
        iP = iL;

    if (iR < n && V[iR].id > V[iP].id)
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_max(V, n, iP);
    }
}

void heapify_max_upwards(Packet_t *V, int32_t n, int32_t i)
{
    // Heapify Max Upwards

    if (i < 0)
        return;

    int32_t iP = i, iL = left(i), iR = right(i);

    if (iL < n && V[iL].id > V[iP].id)
        iP = iL;

    if (iR < n && V[iR].id > V[iP].id)
        iP = iR;

    if (iP != i)
    {
        swap(V, i, iP);
        heapify_max_upwards(V, n, parent(i));
    }
}

void insert(Packet_t *heap, int32_t *heap_len, Packet_t packet)
{
    heap[*heap_len] = packet;
    (*heap_len)++;
}

void insert_max(Packet_t *heap, int32_t *heap_len, Packet_t packet)
{
    heap[*heap_len] = packet;
    (*heap_len)++;

    // printf("\theap_len= %d\tparent = %d\n", (*heap_len), parent(*heap_len));
    heapify_max_upwards(heap, *heap_len, parent((*heap_len) - 1));
    // printf("\t%X Inserido\n", byte);
};

void insert_min(Packet_t *heap, int32_t *heap_len, Packet_t packet)
{
    heap[*heap_len] = packet;
    (*heap_len)++;

    heapify_min_upwards(heap, *heap_len, parent((*heap_len) - 1));
}

void build_heap(Packet_t *V, int32_t n)
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

void build_heap_min(Packet_t *V, int32_t n)
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

void heap_sort_max(Packet_t *V, int32_t n)
{
    build_heap(V, n);

    for (int32_t i = n - 1; i > 0; i--)
    {
        swap(V, 0, i);

        heapify_max(V, i, 0);
    }
}

void heap_sort_min(Packet_t *V, int32_t n)
{
    build_heap_min(V, n);

    for (int32_t i = n - 1; i > 0; i--)
    {
        swap(V, 0, i);

        heapify_min(V, i, 0);
    }
}

void delete_root(Packet_t *V, int32_t *heap_len)
{
    Packet_t last_element = V[(*heap_len) - 1];

    V[0] = last_element;

    (*heap_len)--;

    heapify_min(V, *heap_len, 0);
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
    fscanf(input_fp, "%d %d", &n_total, &seg_len);
    int32_t next_seg = 0 ,next = 0;
    // heap where the packets will be sorted
    Packet_t *heap = (Packet_t *)malloc((n_total + 10) * sizeof(Packet_t));
    int32_t heap_len = 0;

    printf("Tamanho :%d\n", n_total);
    // i =  over Segments
    for (int i = 0; i < n_total; i += seg_len)
    {
        // j = over Segment's Packet
        for (int32_t j = 0; j < seg_len; j++)
        {
            int id, len_packet;
            if (fscanf(input_fp, "%d %d", &id, &len_packet) == EOF)
                break;
            int32_t *data = (int32_t *)malloc(len_packet * sizeof(int32_t));
            // over Packet's data
            for (int k = 0; k < len_packet; k++)
                fscanf(input_fp, "%X", &data[k]);

            Packet_t packet = {
                .data = data,
                .data_len = len_packet,
                .id = id
            };

            // Insert Packet on the heap
            insert_min(heap, &heap_len, packet);
        }

        if(heap[0].id == next){

            fprintf(output_fp, "%d:", next_seg);
            while (heap[0].id == next)
            {
                for (int d = 0; d < heap[0].data_len; d++)
                    fprintf(output_fp, " %02X", heap[0].data[d]);

                delete_root(heap, &heap_len);

                next++;
            }
            fprintf(output_fp,"\n");
            next_seg++;
        }

    }
}