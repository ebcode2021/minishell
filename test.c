#include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>

void	child_process(void)
{
	while (1)
	{
		
	}
	reutrn (0);
}

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		child_process();
	}
	else
	{
		waitpid(-1, 0, 0);
	}
	return (0);
}
