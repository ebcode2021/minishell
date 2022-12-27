# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
typedef struct s_redirection
{
	char	*file_name;
	int		option;
	int		type;
}				t_redirecion;

typedef struct s_exec_block
{
	char				*command;
	char				**args;
	t_redirecion		redirection;
	struct s_exec_block *next;
}				t_exec_block;




void	tmpa(t_exec_block *exec)
{
	if(&(exec->redirection))
		printf("%p", &exec->redirection);
}

int main()
{
	t_exec_block a;

	a.redirection.file_name = 0;
	tmpa(&a);
}
