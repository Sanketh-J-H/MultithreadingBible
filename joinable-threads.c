/**
 * compile-flags: -pthread
 * run-flags:    -out joinable-threads
 * description:  Example demonstrating joinable threads in C using pthreads
 * compilation Environment: GCC on Linux
 * compile using: gcc joinable-threads.c -o joinable-threads -lpthread
 * Execution:    ./joinable-threads
 * author:       Sanketh J H
 * Date:         2025-11-16
 **/
#include <stdio.h>   // standard I/O functions (printf, fprintf, snprintf etc.)
#include <stdlib.h>  // general utilities (exit, malloc, free, EXIT_FAILURE)
#include <pthread.h> // POSIX threads API (pthread_create, pthread_t, pthread_join, pthread_exit)
#include <unistd.h>  // POSIX misc utilities (sleep, pause, usleep, pause)
#include <stdint.h>  // fixed-width integer types (__uint8_t)

static pthread_t thread1;
static pthread_t thread2;

/**
 * @brief Thread callback function that prints a message multiple times
 *
 * This function serves as a callback for a POSIX thread. It prints the message
 * passed as an argument 10 times, sleeping for 500 milliseconds between prints.
 *
 * @param arg Pointer to the message string to be printed
 * @return void* Returns NULL (thread return value)
 **/
static void *thread_fn_callback(void *arg)
{
    int thread_argument = *((int *)arg);
    double *result = malloc(sizeof(double));
    *result = (double)(thread_argument * thread_argument);
    printf("Result from thread with arg %d: %.2f\n", thread_argument, *result);
    while (thread_argument >= 0)
    {
        // printf("Counter %d: \n", thread_argument);
        usleep(500000); // sleep for 500 milliseconds
        thread_argument--;
    }

    printf("Child Thread completed its execution.\n");
    free(arg);
    return (void *)result;
    // pthread_exit(NULL);
}

static void thread_create(pthread_t *thread_handle, int thread_num)
{
    int *__thread_num = calloc(1, sizeof(int));
    *__thread_num = thread_num;
    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_init(&attr);
    if (__thread_num == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    /* Create  thread */
    if (pthread_create(thread_handle, &attr, thread_fn_callback, (void *)__thread_num) != 0)
    {
        fprintf(stderr, "Error creating thread 1\n");
        exit(EXIT_FAILURE);
    }
    else
    {
       printf("Thread %d created successfully.\n", thread_num);
    }
}

int main()
{
    /* Create first thread */
    thread_create(&thread1, 10);
    thread_create(&thread2, 1);

    /* Wait for the first thread to finish */
    printf("Main thread waiting for child thread 1 to complete...\n");
     void *res1;
    if (pthread_join(thread1, &res1) != 0)
    {
        fprintf(stderr, "Error joining thread 1\n");
        exit(EXIT_FAILURE);
    }
   
    if(res1 != NULL)
    {
        double thread1_result = *((double *)res1);
        printf("Thread 1 returned result: %.2f\n", thread1_result);
        free(res1);
    }
    printf("Thread 1 has finished execution.\n");

    /* Wait for the second thread to finish */
    printf("Main thread waiting for child thread 2 to complete...\n");
     void *res2;
    if (pthread_join(thread2, &res2) != 0)
    {
        fprintf(stderr, "Error joining thread 2\n");
        exit(EXIT_FAILURE);
    }
    if(res2 != NULL)
    {
        double thread2_result = *((double *)res2);
        printf("Thread 2 returned result: %.2f\n", thread2_result);
        free(res2);
    }
    printf("Thread 2 has finished execution.\n");

    printf("Main thread exiting.\n");
    return 0;
}