#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int n;
	
	int shm_id;
	int *shmptr;
	key_t key;
	
	scanf("%d", &n);

	key = ftok("~/Document/OSHW4/main.c", 'R');
	shm_id = shmget(key, n * sizeof(int), IPC_CREAT | 0666);
	if (shm_id < 0) {
		fputs("shm failed", stderr);
		exit(1);
	}

	shmptr = shmat(shm_id, (void *)0, 0);
	if ((int)shmptr == -1) {
		perror("shmat error\n");
		goto detachedSHM;	
	}
	puts("Quicksort with multiple processes:\n");
	printf("*** MAIN: shared memory key = %d\n", shm_id);
	puts("*** MAIN: shared memory created");
	puts("*** MAIN: shared memory attached and is ready to use\n");

	
	printf("Input array has %d elements:\n", n);
	for (int i = 0;i < n;++i) {
		scanf("%d",&shmptr[i]); 
		printf("%d  ",shmptr[i]); 	
	}
	puts("\n");

	puts("*** MAIN: about to spawn processes");
	char *para[4];
	for (int i = 0;i < 3;++i)
		para[i] = (char *)calloc(20, sizeof(char));
	
	para[0][0] = '0';
	snprintf (para[1], 10, "%d",n-1);
	snprintf (para[2], 20, "%d",shm_id);
	para[3] = NULL;	

//		printf("### PROC(%u): entering with a[%d..%d]\n", getpid(), 0, n-1);
//		puts("..........");
	int pid = fork();
	if (pid < 0) {
		perror("fork failed");
		goto detachedSHM;	
	}
	if (pid == 0) {
		execvp("./compute", para);
		perror("execvp error\n");
	
	}

	int status = 0;
	wait(&status);

	puts("*** MAIN: sorted array:");
	printf("     ");
	for (int i = 0;i < n;++i)
		printf("%d ", shmptr[i]);
	puts("");

detachedSHM:
	shmctl(shm_id, IPC_RMID, NULL);

	puts("*** MAIN: shared memory successfully detached\n*** MAIN: shared memory successfully removed");
	
}
