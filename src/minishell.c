/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
/*   Updated: 2023/01/06 20:20:20 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_system	g_sys;

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

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_exec_block	*execs;

	if (!argc && !argv)
		return (0);
	set_signal_handler();
	init_system_info(envp);
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
		//system("leaks minishell");
		free(input);
	}
	return (0);
}
