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

int	main(void)
{
	char	*tty;

	tty = ttyname(STDOUT_FILENO);
	printf("%s\n", tty);
	return (0);
}
