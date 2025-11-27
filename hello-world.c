#include <stdio.h>   // standard I/O functions (printf, fprintf, snprintf etc.)
#include <stdlib.h>  // general utilities (exit, malloc, free, EXIT_FAILURE)
#include <pthread.h> // POSIX threads API (pthread_create, pthread_t, pthread_join, pthread_exit)
#include <unistd.h>  // POSIX misc utilities (sleep, pause, usleep, pause)
#include <stdint.h>  // fixed-width integer types (__uint8_t)

static uint8_t count = 0;

/**
 * @brief Thread callback function that continuously prints a message
 *
 * This function serves as a callback for a POSIX thread. It runs in an infinite loop,
 * printing the message passed as argument every second.
 *
 * @param arg Pointer to the message string to be printed
 * @return void* Returns NULL (thread return value)
 *
 * @note the thread will exit after printing the message 10 times
 * to avoid infinite execution in this example.
 **/
static void *thread_fn_callback(void *arg)
{
   
    char *msg = (char *)arg;
    while (1)
    {
        /* code */
        printf("%s %d\n", msg, count);
        usleep(500000); // sleep for 500 milliseconds
        count++;
        if (count == 10)
        {
            printf("Child Thread completed its execution.\n");
            pthread_exit(NULL);
        }
    }
    return NULL;
}

/**
 * @brief Creates a new thread for execution
 *
 * This function initializes and creates a new thread in the program.
 * It handles the thread creation process and allocates necessary resources.
 *
 * @return void
 *
 * @note Thread creation may fail if system resources are exhausted
 */
void thread_create()
{
    /* Thread 1 declaration
     * pthread_t is a data type used to uniquely identify a thread in POSIX
     * compliant systems. It is typically implemented as an unsigned integer or a
     * pointer type, depending on the system architecture.
     * Here, we declare a variable 'thread1' of type pthread_t to hold the ID
     * of the newly created thread.It is commonly called as thread handle.
     */
    pthread_t thread1;

    /* Message to be printed by Thread 1 should be defined before passing to
     * pthread_create and it should not be a local variable , meaning it should
     * have a lifetime that extends beyond the function call. Note : if a local
     * variable is used here, it may lead to undefined behavior as the thread
     * may access invalid memory after the function returns.
     */
    static char *thread1_msg = "Hello World, Thread 1 here!\n";
    /* Create Thread 1 */
    int ret = pthread_create(&thread1, NULL, thread_fn_callback, (void *)thread1_msg);
    if (ret)
    {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", ret);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    thread_create();

    // printf("Main thread is Paused.\n");
    // pause();
    printf("Main thread completed its execution.\n");
    pthread_exit(NULL); // terminate main thread but keep process alive until other threads exit

    return 0;
}
