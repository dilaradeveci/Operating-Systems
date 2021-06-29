#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  	printf("Base Process ID: %d, level: 0 \n", getpid());
	
  	int level = 0;

 	for (int i = 0; i < 4; i++) {

    	pid_t pid = fork();

    	if (pid == 0) {

	      level++;
	      printf("Process ID: %d, Parent ID: %d, level: %d \n", getpid(), getppid(), level);

    }
    	else if (pid > 0) {
	wait(NULL);	
	}
  }
  	sleep(1);
	return 0;
}
