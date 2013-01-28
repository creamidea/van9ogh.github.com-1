#include <unistd.h>     
#include <sys/types.h>  
#include <errno.h>      
#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>    
#include <string.h>     
#include <semaphore.h>  

sem_t semaphore;
int counter;

void* th_handler (void *args)
{
    int x; 
    x = *((int *)args);
    printf("Thread %d: Waiting to enter critical region...\n", x);
    sem_wait(&semaphore);
	// 临界区代码
    printf("Thread %d: Now in critical region...\n", x);
    printf("Thread %d: Counter Value: %d\n", x, counter);
    printf("Thread %d: Incrementing Counter...\n", x);
    counter++;
    printf("Thread %d: New Counter Value: %d\n", x, counter);
    printf("Thread %d: Exiting critical region...\n", x);
	// END
    sem_post(&semaphore);
    
    pthread_exit((void *)0);
}

int main(void)
{
    int args[2] = {1, 2};
    pthread_t thread_a;
    pthread_t thread_b;
    
	/* 第二个参数: 
	 *		当参数为0表示: is shared between the threads of a process
	 * 		非0          : is shared between processes, and should be located in a region of shared memory
	 *  第三个参数:
	 *		指定信号量的初始值
     */
    sem_init(&semaphore, 0, 1);
                                 
    pthread_create (&thread_a, NULL, th_handler, (void *)&args[0]);
    pthread_create (&thread_b, NULL, th_handler, (void *)&args[1]);
    
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

	sem_destroy(&semaphore);
                  
    exit(0);
}
