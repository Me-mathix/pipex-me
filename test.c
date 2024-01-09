#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int fd[2];
	char c;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		printf("FORK ERROR");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve("/bin/ls", argv, envp);
		printf("This line will not be executed.\n");
	}
	if (pid > 0)
	{
		printf("%s\n", "je suis papa enfin");
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve("/bin/sort", 0, envp);
	}
	printf("are u winning son ?");
	return (0);
}