#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*arr[4];

	arr[0] = "ls";
	arr[1] = "\"-al\"";
	arr[2] = 0;
	arr[3] = 0;
	execve("/bin/cat", arr, envp);
	return (0);
}