#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
		pid = fork();
		if (pid > 0) {
			sleep(10);
		}
		wait(NULL);

return 0;
}
