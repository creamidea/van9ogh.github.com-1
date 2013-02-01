#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore *//*}*/
#include <sys/shm.h>

#define TEXT_SZ 2048

int main(void)
{
	int shmid;
	sem_t *semaphore;

	shmid = shmget((key_t)1234, sizeof(sem_t), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_SUCCESS);
	}

	semaphore = shmat(shmid, (void *)0, 0);
	if (semaphore == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_SUCCESS);
	}


	printf("Memory attached at %X\n", (int)semaphore);

	sem_init(semaphore, 1, 1);
	

	exit(EXIT_SUCCESS);
}
