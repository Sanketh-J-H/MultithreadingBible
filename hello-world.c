#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *thread_fn_callback(void *arg)
{
    char *msg = (char *)arg;
    while (1)
    {
        /* code */
        printf("%s", msg);
        sleep(1);
    }
    return NULL;
}

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

    printf("Main thread is Paused.\n");
    pause();

    return 0;
}
