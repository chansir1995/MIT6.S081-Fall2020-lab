#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
	int p[2], pid;
	char buf[1];
  if(argc != 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }
  pipe(p);
  if(fork() == 0){
  	pid = getpid();	
  	read(p[0], buf, 1);
  	//close(p[0]);
  	fprintf(1, "%d: received ping\n", pid);
  	write(p[1], buf, 1);
  	close(p[1]);
  }else{
  	pid = getpid();	
  	write(p[1], buf, 1);
  	wait((int*) 0);
  	read(p[0], buf, 1);
  	close(p[0]);
  	fprintf(1, "%d: received pong\n", pid);
  }
  exit(0);
}
/*
//通过两个管道实现，有点多余
int
main(int argc, char *argv[]){
	int p1[2], p2[2], pid;
	char buf[1];
  if(argc != 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }
  pipe(p1);
  pipe(p2);
  if(fork() == 0){
  	close(p1[1]);
  	close(p2[0]);
  	pid = getpid();	
  	read(p1[0], buf, 1);
  	close(p1[0]);
  	fprintf(1, "%d: received ping\n", pid);
  	write(p2[1], buf, 1);
  	close(p2[1]);
  }else{
  	close(p1[0]);
  	close(p2[1]);
  	pid = getpid();	
  	write(p1[1], buf, 1);
  	close(p1[1]);
  	read(p2[0], buf, 1);
  	close(p2[0]);
  	fprintf(1, "%d: received pong\n", pid);
  }
  exit(0);
}
*/
