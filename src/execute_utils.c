/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:10:51 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 20:38:43 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pipe_n_fork(t_pipe *new_pipe)
{
	pid_t	pid;

	if (new_pipe)
		pipe(new_pipe->fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, signal_interrupt);
		signal(SIGQUIT, signal_quit);
	}
	else if (pid == -1)
	{
		print_custom_error(0, 0, FORK_ERR);
		g_sys.last_errno = errno;
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	set_current_cmd(t_exec_block *execs)
{
	t_list	*new_lst;
	char	*data;

	ft_lst_remove_if(&g_sys.env_lst, "_");
	if (!execs->command || execs->next)
		return ;
	data = ft_strjoin("_=", execs->command);
	new_lst = ft_lstnew(data);
	ft_lstadd_back(&g_sys.env_lst, new_lst);
}
