#include "implementation.h"

int main()
{
    printf("Num Sub-Buffers, Num Threads: %d, Num Elements per Sub-Buffer: %d\n",
           NUM_SUB_BUFFERS, NUM_ELEMENTS);
    init_buffer();

    product_multi();
    product_no_multi();

    exit(EXIT_SUCCESS);
}
