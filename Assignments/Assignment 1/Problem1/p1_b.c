#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid == 0) {       		
		char *path = "/bin/ps";
  		char *args[]= {path, "-f", 0};
 		execv(path, args);
		}
        if (pid > 0) {
        	wait(NULL);
		printf("Child finished execution\n");
         		}
        return 0;
}
