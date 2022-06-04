#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* argv[0]: start index
 * argv[1]: end index
 * argv[2]: shm_id
 */
int main(int argc, char **argv) 
{
	int start_index = atoi(argv[0]);
	int end_index    = atoi(argv[1]);
	int shm_id      = atoi(argv[2]);

	int *shmptr = shmat(shm_id, (void *)0, 0);

	printf("### PROC(%ui): entering with a[%d..%d]\n", getpid(), start_index, end_index);
	for (int i = start_index;i < end_index;i++) {
		printf("%d ", shmptr[i]);
	}		
	return 0;	
}
