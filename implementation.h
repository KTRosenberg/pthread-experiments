#ifndef PTHREAD_TESTING_1_IMPLEMENTATION_H
#define PTHREAD_TESTING_1_IMPLEMENTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>

#define NUM_SUB_BUFFERS 5
#define NUM_ELEMENTS 200000000

extern double buffer[NUM_SUB_BUFFERS][NUM_ELEMENTS];

void init_buffer();
void product_no_multi();
void* multi_procedure(void* id);
void product_multi();

typedef struct thread_data
{
    double* sub_buffer;
    double sub_product;
}thread_data_t;

int32_t allocate_data_structs(thread_data_t** args);
void free_data_structs(int32_t d, thread_data_t** args);

#endif
