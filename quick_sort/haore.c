#include <stdint.h>


int32_t *vector_ptr[];

void swap(int32_t *array_ptr, int source_pos, int dest_pos)
{
    // printf("Swapping %d <-> %d\n", source_pos, dest_pos);
    int32_t temp = array_ptr[dest_pos];

    array_ptr[dest_pos] = array_ptr[source_pos];
    array_ptr[source_pos] = temp;
}

int32_t haore(int32_t *vector, int32_t pivot_pos ){

}


int main(int argc, char* argv[]){


}