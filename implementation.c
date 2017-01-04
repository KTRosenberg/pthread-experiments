#include "implementation.h"

double buffer[NUM_SUB_BUFFERS][NUM_ELEMENTS];


void init_buffer()
{
    int32_t sub_buffer = 0;
    for (; sub_buffer < NUM_SUB_BUFFERS; sub_buffer++)
    {
        int64_t i = 0;
        for (; i < NUM_ELEMENTS; i++)
        {
            buffer[sub_buffer][i] = i+1 ? i+1 : 1;
        }
    }
}


void product_no_multi()
{
    double product = 1;

    time_t start_time = 0;
    time_t end_time = 0;

    int32_t sub_buffer = 0;
    time(&start_time);
    for (; sub_buffer < NUM_SUB_BUFFERS; sub_buffer++)
    {
        int32_t i = 0;
        for (; i < NUM_ELEMENTS; i++)
        {
            product *= buffer[sub_buffer][i];
            if (product == 0)
            {
            	product = 1;
            }
        }
    }

    time(&end_time);

    printf("NO MULTI:\nTime = (end %fs) - (start %fs) = (%fs)\n", 
           difftime(end_time, 0), 
           difftime(start_time, 0), 
           difftime(end_time, start_time));

}


void* multi_procedure(void* id)
{
    thread_data_t* data = (thread_data_t*)id;
    double* sub_buffer = data->sub_buffer;
    double product = 1;
    int32_t i = 0;
    for(; i < NUM_ELEMENTS; i++)
    {
        product *= sub_buffer[i];
        if (product == 0)
        {
        	product = 1;
        }
    }

    data->sub_product = product;

    return NULL;
}


void product_multi()
{
    double product = 1;
    pthread_t threads[NUM_SUB_BUFFERS];
    thread_data_t* args[NUM_SUB_BUFFERS];

    int32_t d = 0;
    if ((d = allocate_data_structs(args)) != 0)
    {
        free_data_structs(d, args);
        exit(EXIT_FAILURE);
    }

    time_t start_time = 0;
    time_t end_time = 0;

    time(&start_time);

    int32_t status = 0;
    for (int32_t t = 0; t < NUM_SUB_BUFFERS; t++)
    {
        status = pthread_create(&threads[t],
                                NULL,
                                multi_procedure,
                                args[t]);
        if (status)
        {
            perror("THREAD CREATION UNSUCCESSFUL");
            exit(EXIT_FAILURE);
        }
    }

    for (int t = 0; t < NUM_SUB_BUFFERS; t++)
    {
        pthread_join(threads[t], NULL);
        product *= args[t]->sub_product;
    }

    time(&end_time);

    printf("MULTI:\nTime = (end %fs) - (start %fs) = (%fs)\n", 
           difftime(end_time, 0), 
           difftime(start_time, 0), 
           difftime(end_time, start_time));

    free_data_structs(NUM_SUB_BUFFERS, args);

}


int32_t allocate_data_structs(thread_data_t** args)
{
    int32_t d = 0;
    for (; d < NUM_SUB_BUFFERS; d++)
    {
        thread_data_t* arg = malloc(sizeof(thread_data_t));
        if (!arg)
        {
            perror("MEMORY ALLOCATION UNSUCCESSFUL");
            return d;
        }

        thread_data_t data = {.sub_buffer = buffer[d], .sub_product = 0};
        (*arg) = data;
        args[d] = arg;
    }

    return 0;
}


void free_data_structs(int32_t d, thread_data_t** args)
{
    int32_t f = 0;
    for (; f < d; f++)
    {
        free(args[f]);
    }
}
