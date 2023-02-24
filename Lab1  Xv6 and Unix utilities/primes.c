#include "kernel/types.h"
#include "user/user.h"
void
start(int* p){
	close(p[1]);
	int cur, first;
	if(read(p[0], &cur, sizeof(int)) != 0){
		first = cur;
		fprintf(1, "prime %d\n", first);
		int pnext[2];
		pipe(pnext);
		while(read(p[0], &cur, sizeof(int)) != 0){
			if(cur % first != 0)	
				write(pnext[1], &cur, sizeof(int));
		}
		close(p[0]);
		close(pnext[1]);
		if(fork() == 0){
			start(pnext);
		}
		else{
			close(pnext[0]);
			wait(0);
		}
	}
	exit(0);	
}

int
main(int argc, char* argv[]){
	if(argc != 1){
		fprintf(2, "primes has no argument\n");
		exit(1);
	  }
	int p[2];
	pipe(p);
	for(int i = 2; i <= 35; ++i)
		write(p[1], &i, sizeof(int));
	if(fork() == 0)
		start(p);
	else{
		close(p[1]);
		close(p[0]);
		wait(0);
	}
	exit(0);
}
