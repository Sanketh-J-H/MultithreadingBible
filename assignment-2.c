/**
 * This program takes an Integer input N from the user and creates sequential threads
 * where each thread N prints N thread prints N-1 and so on till 0 is reached.
 * Author: Sanketh J H
 * Date: 2025-11-18
 **/
#include <stdio.h>   // standard I/O functions (printf, fprintf, snprintf etc.)
#include <stdlib.h>  // general utilities (exit, malloc, free, EXIT_FAILURE)
#include <pthread.h> // POSIX threads API (pthread_create, pthread_t, pthread_join, pthread_exit)
#include <unistd.h>  // POSIX misc utilities (sleep, pause, usleep, pause)
#include <stdint.h>  // fixed-width integer types (__uint8_t)

pthread_t pthread_main;
static int counter = 0;

void* thread_fn_callback(void *arg)
{
    int* thread_argument = (int *)calloc(1, sizeof(int));
    *thread_argument = *(int *)arg;
    // free(arg);

    return (void *)thread_argument;
}

void thread_create(pthread_t *thread_handle, void* thread_argument)
{
   
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int rc = pthread_create(thread_handle,
                            &attr,
                            thread_fn_callback,
                            thread_argument);
    if (rc != 0)
    {
        printf("Error occurred, thread could not be created, errno = %d\n", rc);
        exit(0);
    }
}

int main()
{
    int n;
    printf("Enter a positive integer N to create N sequential threads: ");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    pthread_main = pthread_self();

    for (counter = n; counter >= 0; counter--)
    {
        pthread_t new_thread;
        thread_create(&new_thread,(void *) &counter);
        void *result;
        if (pthread_join(new_thread, &result) != 0)
        {
            fprintf(stderr, "Error joining thread %d\n", counter);
            return EXIT_FAILURE;
        }
        printf("Main Thread Paued and waiting for Thread %d to complete.\n", counter);
        if (result != NULL)
        {
            int thread_result = *((int *)result);
            printf("Thread %d returned result: %d\n", counter, thread_result);
            free(result);
        }
    }

    printf("All threads completed execution.\n");
    return EXIT_SUCCESS;
}