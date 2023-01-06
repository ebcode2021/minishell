/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:10:51 by eunson            #+#    #+#             */
/*   Updated: 2023/01/06 18:48:28 by eunson           ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	return (pid);
}

char	*last_arguemnt(char **arguments)
{
	size_t	idx;

	idx = 0;
	if (!arguments[idx])
		return (arguments[0]);
	while (arguments[idx])
		idx++;
	return (arguments[idx - 1]);
}

void	update_current_argument(t_exec_block *execs)
{
	t_list	*new_lst;
	char	*data;

	ft_lst_remove_if(&g_sys.env_lst, "_");
	if (!execs->command || execs->next)
		return ;
	data = ft_strjoin("_=", last_arguemnt(execs->args));
	new_lst = ft_lstnew(data);
	ft_lstadd_back(&g_sys.env_lst, new_lst);
}

void	update_exit_status_code(void)
{
	t_list	*elem;
	char	*joined;
	char	*str_num;

	str_num = ft_itoa(g_sys.last_exit_status_code);
	joined = ft_strjoin("?=", str_num);
	ft_lst_remove_if(&g_sys.env_lst, "?");
	elem = ft_lstnew(joined);
	ft_lstadd_back(&g_sys.env_lst, elem);
	free(joined);
	free(str_num);
}
