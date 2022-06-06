#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SWAP(x, y) do { x ^= y; \
	y ^= x; \
	x ^= y; \
} while(0);


/* argv[0]: start index
 * argv[1]: end index
 * argv[2]: shm_id
 */
int main(int argc, char **argv) 
{
	int start_index = atoi(argv[0]);
	int end_index   = atoi(argv[1]);
	int shm_id      = atoi(argv[2]);

	int *shmptr = shmat(shm_id, (void *)0, 0);

	if (start_index >=  end_index) {
		printf("   ### PROC(%d): exits\n", getpid());
		puts("      ..........");
		return 0;
	}
	printf("   ### PROC(%d): entering with a[%d..%d]\n", getpid(), start_index, end_index);
	puts("      ..........");
	printf("      ");
	for (int i = start_index;i <= end_index;i++) {
		printf("%d ", shmptr[i]);
	}		
	puts("");

	int i, j;
	for (i = start_index, j = end_index - 1;i < j;) {

		while (i < j && shmptr[i] < shmptr[end_index])
			i++;
		while (i < j && shmptr[j] > shmptr[end_index])
			j--;

		if (i < j) {
			SWAP(shmptr[i], shmptr[j]);
		} else break;
	}
	if (j != end_index - 1) {
		SWAP(shmptr[j], shmptr[end_index]);
 		printf("   ### PROC(%d): partition position is a[%d] = %d\n", getpid(), j, shmptr[j]);  
		puts("      ..........");
	}
	

	char *para1[4];
	char *para2[4];

	for (int i = 0;i < 3;++i) {
		para1[i] = (char *)calloc(15, sizeof(char));
		para2[i] = (char *)calloc(15, sizeof(char));
	}

	strcpy(para1[0], argv[0]);
	snprintf(para1[1], 10, "%d", i - 1);
	strcpy(para1[2], argv[2]);

	snprintf(para2[0], 10, "%d", i + 1);
	strcpy(para2[1], argv[1]);
	strcpy(para2[2], argv[2]);

	para1[3] = para2[3] = NULL;
	

	int pid1 = fork();
	if (pid1 == 0) {
		/* Sort top half array */
		execvp("./compute", para1);
		fprintf(stdout, "%u: fork failed", getpid());
	}

	int pid2 = fork();
	if (pid2 == 0) {
		/* Sort bottom half array */
		execvp("./compute", para2);
		fprintf(stdout, "%u: fork failed", getpid());
	}

	int status, status1;
	wait(&status);
	wait(&status1);

	return 0;	
}

