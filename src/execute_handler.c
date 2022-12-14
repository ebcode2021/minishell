/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:30:49 by eunson            #+#    #+#             */
/*   Updated: 2023/01/10 14:33:47 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_exec_block *exec, t_pipe *iter_pipe)
{
	change_pipe_fd(exec, iter_pipe);
	set_redirection_fd(exec, CHILD);
	if (exec->command)
	{
		if (is_builtin(exec->command))
			builtin_handler(exec, CHILD);
		else
			command_handler(exec);
	}
	exit(EXIT_FAILURE);
}

static void	single_execute(t_exec_block *exec)
{
	pid_t	pid;
	int		status;

	pid = pipe_n_fork(0);
	status = 0;
	if (pid == 0)
	{
		set_redirection_fd(exec, CHILD);
		if (exec->command)
			status = command_handler(exec);
		exit(status);
	}
	waitpid(pid, &status, 0);
	child_exit_handler(status);
}

static void	execute(t_exec_block *execs)
{
	pid_t			*pid_list;
	t_pipe			iter_pipe;
	t_exec_block	*head;
	size_t			idx;

	idx = 0;
	iter_pipe.prev_fd = -1;
	head = execs;
	pid_list = ft_calloc(1, BUFFER_SIZE);
	while (head && !g_sys.signal)
	{
		pid_list[idx] = pipe_n_fork(&iter_pipe);
		if (pid_list[idx++] == 0)
			child_process(head, &iter_pipe);
		close(iter_pipe.prev_fd);
		close(iter_pipe.fd[WRITE]);
		iter_pipe.prev_fd = iter_pipe.fd[READ];
		head = head->next;
	}
	close(iter_pipe.fd[READ]);
	idx = 0;
	while (pid_list[idx])
		waitpid(pid_list[idx++], &g_sys.last_exit_status_code, 0);
	free(pid_list);
	child_exit_handler(g_sys.last_exit_status_code);
}

void	execute_handler(t_exec_block *execs)
{
	if (g_sys.signal || !execs)
		return ;
	update_current_argument(execs);
	if (execs->next)
		execute(execs);
	else
	{
		if (is_builtin(execs->command))
		{
			set_redirection_fd(execs, PARENTS);
			builtin_handler(execs, PARENTS);
		}
		else
			single_execute(execs);
	}
	update_exit_status_code();
}
