#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMELTS 16384

// Implements the naive primality test.
// Returns TRUE if n is a prime number
int prime(int n)
{
	int ret=1, i;
	for(i=2; i<=(int) sqrt(n) && ret; i++)
		ret=n % i;
	return ret;
}

int main()
{
	int data[NUMELTS];
	int fd[2];
	int buffer;
	int i;

	srand(time(NULL));
	pipe(fd);

	for(i=0; i<NUMELTS; i++)
		data[i]= (int) (((double) rand() / (double) RAND_MAX) * 10000);
	
	pid_t pid = fork();

	if(pid) {

		int pCount = 0;

		for(i = 0; i < (NUMELTS/2); i++) {
			if(prime(data[i]))
				pCount++;
		}

		wait(&pid);

		close(fd[1]);
		read(fd[0], &buffer, sizeof(buffer));
		printf("Primes found by parent = %d, found by child = %d, total = %d\n", pCount, buffer, pCount + buffer);

	}

	else {

		int cCount = 0;

		for(i = (NUMELTS/2); i < NUMELTS; i++) {
			if(prime(data[i])) { 
				cCount++;
			}
		}

		close(fd[0]);
		write(fd[1], &cCount, sizeof(cCount));
		exit(1);
	}
}
