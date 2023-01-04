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
	printf("%s\n", str_replace(argv[1], "\'", ""));
}
