#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

int	main(int argc, char **argv, char **envp)
{
	char	*tty;
	char	*args[3] = {"mkdir", "/tmp/picoshell/", 0};
	char	*rm[4] = {"rm", "-rf", "/tmp/picoshell/", 0};
	pid_t	pid;

	if (opendir("/tmp/picoshell/") == 0)
	{
		printf("hi1\n");
		perror("/tmp/picoshell");
		printf("hi2\n");
		pid = fork();
		if (pid == 0)
			execve("/bin/rm", rm, envp);
		printf("hi3\n");
		pid = fork();
		if (pid == 0)
			execve("/bin/mkdir", args, envp);
		printf("hi4\n");
	}
	return (0);
}
