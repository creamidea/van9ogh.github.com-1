#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>


/* 
	本程序为使用信号量的例子, 一个程序打印XX， 一个程序打印OO
	使用pv操作后O与X不会出现单个， 都是成双出现的.即使X与X，O
	与O是间隔我们故意放慢了脚步
	Usage:
		./a.out 1 & ./a.out
	output:
	0000XX00XX00XX00XX00XX00XX00XX00XX00
 */


/*	这个数据类型用在semctl函数的第四个参数
	int semctl(int sem_id, int sem_num, int command, ...);
	它和command联合使用:
	command:
		SETVAL: 初始化信号量值
		IPC_RMID: 删除已经无需使用的信号量标示符
 */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

static int set_semvalue(void);
static void del_semvalue(void);
static int sem_operation_p(void);
static int sem_operation_v(void);

static int sem_id;

int main(int argc, char *argv[])
{
	int i;
	int pause_time;
	char op_char = '0';

	srand((unsigned int)getpid());
	// 创建信号量
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
	if (argc > 1) {
		// 当参数大于1个时候, 初始化信号量, 让op_char 为 'X'
		if (!set_semvalue()) {
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_SUCCESS);
		}
		op_char = 'X';
		sleep(2);
	}
	for (i = 0; i < 10; i++) {
		// 执行p操作， 减1
		if (!sem_operation_p()) exit(EXIT_SUCCESS);
		printf("%c", op_char);fflush(stdout);
		// 休息（随机数，(0, 3])s
		pause_time = rand() % 3;
		sleep(pause_time);
		printf("%c", op_char);fflush(stdout);
		// 执行v操作， 加1
		if (!sem_operation_v()) exit(EXIT_SUCCESS);
		// 休息（随机数，(0, 2])s
		pause_time = rand() % 2;
		sleep(pause_time);
	}

	printf("\n%d - finished\n", getpid());

	if (argc > 1) {
		sleep(10);
		del_semvalue();
	}

	exit(EXIT_SUCCESS);
}

static int set_semvalue(void)
{
	union semun sem_union;
	sem_union.val = 1;
	// 设置信号量的值为1
	if (semctl(sem_id, 0, SETVAL, sem_union) == 1) return 0;
	return 1;
}

static void del_semvalue(void)
{
	union semun sem_union;
	
	// 删除信号量标示符
	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) 
		fprintf(stderr, "Failed to delete semaphore\n");
}

static int sem_operation_p(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1; // p operation
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semophore_p failed\n");
		return 0;
	}

	return 1;
}

static int sem_operation_v(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; // v operation
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semophore_v failed\n");
		return 0;
	}

	return 1;
}
