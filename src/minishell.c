/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 14:32:10 by eunson           ###   ########.fr       */
=======
/*   Updated: 2023/01/05 13:33:36 by jinholee         ###   ########.fr       */
>>>>>>> feature/export
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_system	g_sys;

void	set_tmp_dir(char **envp)
{
	DIR			*dir;
	pid_t		pid;
	char *const	rm_args[4] = {"rm", "-rf", g_sys.tmp_dir, 0};
	char *const	mkdir_args[4] = {"mkdir", "-p", g_sys.tmp_dir, 0};

	dir = opendir(g_sys.tmp_dir);
	if (dir == 0)
	{
		pid = pipe_n_fork(0);
		if (pid == 0)
		{
			execve("/bin/rm", rm_args, envp);
			exit(1);
		}
		waitpid(pid, 0, 0);
		pid = pipe_n_fork(0);
		if (pid == 0)
		{
			execve("/bin/mkdir", mkdir_args, envp);
			exit(1);
		}
		return ;
		waitpid(pid, 0, 0);
	}
	closedir(dir);
}

void	clean_up(void)
{
	pid_t		pid;
	char		**envp;
	char *const	rm_args[4] = {"rm", "-rf", g_sys.tmp_dir, 0};

	pid = pipe_n_fork(0);
	if (pid == 0)
	{
		envp = current_env_lst();
		execve("/bin/rm", rm_args, envp);
		exit(1);
	}
	waitpid(pid, 0, 0);
}

void	set_g_system_info(char *envp[])
{
	t_list	*env;

	getcwd(g_sys.pwd, BUFFER_SIZE);
	g_sys.tmp_dir = ft_strjoin(TMP_DIRECTORY, ttyname(STDIN_FILENO));
	set_tmp_dir(envp);
	g_sys.env_lst = 0;
	while (*envp)
		ft_lstadd_back(&g_sys.env_lst, ft_lstnew(*envp++));
	ft_lstadd_back(&g_sys.env_lst, ft_lstnew("?=0"));
	g_sys.home_dir = g_sys.pwd;
	env = ft_lstfind(g_sys.env_lst, "HOME");
	if (env)
		g_sys.home_dir = env->value;
	env = ft_lstfind(g_sys.env_lst, "OLDPWD");
	free(env->value);
	env->value = 0;
	g_sys.last_errno = 0;
	g_sys.last_exit_status_code = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_exec_block	*execs;

	if (!argc && !argv)
		return (0);
	set_signal_handler();
	set_g_system_info(envp);
	while (1)
	{
		input = readline("picoshell> ");
		if (input)
			add_history(input);
		else
			pseudo_sigterm();
		if (syntax_check(input))
		{
			execs = exec_block_parser(input);
			execute_handler(execs);
			free_blocks(execs);
			reset_fd();
		}
		//g_system("leaks minishell");
		free(input);
	}
	return (0);
}
