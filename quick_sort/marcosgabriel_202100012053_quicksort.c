#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* ------ Global ------ */
uint32_t call_count = 0;

typedef enum
{
    LP = 0,
    LM,
    LA,
    HP,
    HM,
    HA,
} Type;

typedef struct Sort
{
    char *type;
    int32_t call_count;
} Sort_t;

/* ------ Utils ------ */
void swap(int32_t *array_ptr, int source_pos, int dest_pos)
{
    call_count++;
    int32_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

void swap_Sort(Sort_t *array_ptr, int source_pos, int dest_pos)
{
    Sort_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

int32_t median(int a, int b, int c, int32_t n, int32_t lo)
{
    if ((a >= b && a <= c) || (a <= b && a >= c))
        return lo + (n / 4); // a
    else if ((b > a && b <= c) || (b < a && b >= c))
        return lo + (n / 2); // b
    else
        return lo + (3 * n / 4); // c
}

/* -------------------- */
/* ------ Hoare ------- */
/* -------------------- */

int32_t hoare_partition(int32_t *vector, int32_t low, int32_t high) // i = first position ; j = last position
{
    // aka: HP(x)

    // Arbitrary Pivot.
    int32_t P = vector[low], x = low - 1, y = high + 1;

    while (true)
    {
        while (vector[--y] > P)
            ;
        while (vector[++x] < P)
            ;
        if (x < y)
            swap(vector, x, y);
        else
            return y;
    }
}

int32_t hoare_median(int32_t *vector, int32_t low, int32_t high) // i = first position ; j = last position
{
    // aka: HM(x)

    int32_t n = high - low + 1;

    int32_t a = vector[low + (n / 4)], b = vector[low + (n / 2)], c = vector[low + (3 * n / 4)];

    int32_t k = median(a, b, c, n, low);

    swap(vector, low, k);

    return hoare_partition(vector, low, high);
}

int32_t hoare_rand(int32_t *vector, int32_t low, int32_t high)
{
    // aka: HA(x)

    int32_t k = (low + (abs(vector[low]) % (high - low + 1)));

    swap(vector, low, k);

    return hoare_partition(vector, low, high);
}

/* -------------------- */
/* ------ Lomuto ------ */
/* -------------------- */

int32_t lomuto_partition(int32_t *vector_ptr, int32_t i, int32_t j)
{
    // aka: LP(x)

    int32_t P = vector_ptr[j], x = i - 1, y = i;

    for (y = i; y < j; y++)
        if (vector_ptr[y] <= P)
            swap(vector_ptr, ++x, y);

    swap(vector_ptr, ++x, j);

    return x;
}

int32_t lomuto_rand(int32_t *vector, int32_t i, int32_t j)
{
    // aka: LA(x)

    swap(vector, j, (i + (abs(vector[i]) % (j - i + 1))));

    return lomuto_partition(vector, i, j);
}

int32_t lomuto_median(int32_t *vector, int32_t low, int32_t high)
{
    // aka: LM(x)

    int32_t n = high - low + 1;

    int32_t a = vector[low + (n / 4)], b = vector[low + (n / 2)], c = vector[low + (3 * n / 4)];

    int32_t k = median(a, b, c, n, low);

    swap(vector, high, k);

    return lomuto_partition(vector, low, high);
}

/* ----------------------- */
/* ------ QuickSort ------ */
/* ----------------------- */
void recursive_quicksort(int32_t *vector_ptr, int32_t low, int32_t high, Type type)
{
    call_count++;
    int32_t pivot;

    if (low < high)
    {
        switch (type)
        {
        case LP:
            pivot = lomuto_partition(vector_ptr, low, high);
            recursive_quicksort(vector_ptr, low, pivot - 1, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);

            break;

        case LM:
            pivot = lomuto_median(vector_ptr, low, high);
            // sorting by partitioning;

            recursive_quicksort(vector_ptr, low, pivot - 1, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);

            break;

        case LA:
            pivot = lomuto_rand(vector_ptr, low, high);

            recursive_quicksort(vector_ptr, low, pivot - 1, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);
            break;

        case HP:
            pivot = hoare_partition(vector_ptr, low, high);
            // sorting by partitioning;

            recursive_quicksort(vector_ptr, low, pivot, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);
            break;

        case HM:
            pivot = hoare_median(vector_ptr, low, high);
            // sorting by partitioning;

            recursive_quicksort(vector_ptr, low, pivot, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);
            break;

        case HA:
            pivot = hoare_rand(vector_ptr, low, high);
            // sorting by partitioning;

            recursive_quicksort(vector_ptr, low, pivot, type);
            recursive_quicksort(vector_ptr, pivot + 1, high, type);
            break;
        }
    }
}

/* ----------------------- */
/* -------- Call --------- */
/* ----------------------- */

int32_t insertion_sort(Sort_t *sort, int32_t n)
{
    int i, j;
    Sort_t chave;

    for (i = 1; i < n; i++)
    {
        chave = sort[i];
        j = i - 1;

        while (j >= 0 && sort[j].call_count > chave.call_count)
        {
            sort[j + 1] = sort[j];
            j = j - 1;
        }
        sort[j + 1] = chave;
    }
    return 0;
}

/* ----------------------- */
/* -------- Main --------- */
/* ----------------------- */

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Quantidade incorreta de argumentos!");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    FILE *output_fp = fopen(argv[2], "w");

    int32_t vectors_count, vector_len;
    int32_t *lp_ptr, *lm_ptr, *la_ptr, *hp_ptr, *hm_ptr, *ha_ptr;

    fscanf(input_fp, "%d", &vectors_count);

    for (int i = 0; i < vectors_count; i++)
    {
        fscanf(input_fp, "%d", &vector_len);

        // unsorted vector
        lp_ptr = malloc(vector_len * sizeof(int32_t));

        for (int j = 0; j < vector_len; j++)
            fscanf(input_fp, "%d", &lp_ptr[j]);

        lm_ptr = malloc(vector_len * sizeof(int32_t));
        memcpy(lm_ptr, lp_ptr, vector_len * sizeof(int32_t));

        la_ptr = malloc(vector_len * sizeof(int32_t));
        memcpy(la_ptr, lp_ptr, vector_len * sizeof(int32_t));

        hp_ptr = malloc(vector_len * sizeof(int32_t));
        memcpy(hp_ptr, lp_ptr, vector_len * sizeof(int32_t));

        hm_ptr = malloc(vector_len * sizeof(int32_t));
        memcpy(hm_ptr, lp_ptr, vector_len * sizeof(int32_t));

        ha_ptr = malloc(vector_len * sizeof(int32_t));
        memcpy(ha_ptr, lp_ptr, vector_len * sizeof(int32_t));

        Sort_t sort[6];

        call_count = 0;
        sort[LP].type = "LP";
        recursive_quicksort(lp_ptr, 0, vector_len - 1, LP);
        sort[LP].call_count = call_count;

        call_count = 0;
        sort[LM].type = "LM";
        recursive_quicksort(lm_ptr, 0, vector_len - 1, LM);
        sort[LM].call_count = call_count;

        call_count = 0;
        sort[LA].type = "LA";
        recursive_quicksort(la_ptr, 0, vector_len - 1, LA);
        sort[LA].call_count = call_count;

        call_count = 0;
        sort[HP].type = "HP";
        recursive_quicksort(hp_ptr, 0, vector_len - 1, HP);
        sort[HP].call_count = call_count;

        call_count = 0;
        sort[HM].type = "HM";
        recursive_quicksort(hm_ptr, 0, vector_len - 1, HM);
        sort[HM].call_count = call_count;

        call_count = 0;
        sort[HA].type = "HA";
        recursive_quicksort(ha_ptr, 0, vector_len - 1, HA);
        sort[HA].call_count = call_count;

        fprintf(output_fp, "%d: N(%d)", i, vector_len);

        insertion_sort(sort, 6);

        for (int j = 0; j < 6; j++)
            fprintf(output_fp, " %s(%d)", sort[j].type, sort[j].call_count);

        fprintf(output_fp, "\n");
    }
}