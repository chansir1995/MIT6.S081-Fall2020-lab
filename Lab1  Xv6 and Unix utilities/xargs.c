#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
  if(argc < 2 || argc > MAXARG - 1){
    fprintf(2, "Usage: xargs <functions> <argv>...\n");
    exit(1);
  }
  char buf[128];
	char *argvN[MAXARG];
	for(int i = 0; i < argc - 1 && i < MAXARG; ++i){
		argvN[i] = argv[i + 1];
	}
	argvN[argc] = 0;
	int index = 0;
	while(read(0, buf + index, 1) == 1){
		if(buf[index] == '\n'){
			buf[index] = '\0';
			argvN[argc - 1] = buf;
			if(fork() == 0){
				exec(argv[1], argvN);
				fprintf(2, "exec error\n");
			}else{
				index = 0;
				wait(0);
			}
		}
		else
			++index;
	}
  exit(0);
}