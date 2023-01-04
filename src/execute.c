/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:30:49 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 13:42:23 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pipe_n_fork(t_pipe *new_pipe)
{
	pid_t	pid;

	if (new_pipe)
		pipe(new_pipe->fd);
	pid = fork();
	return (pid);
}

void	child_process(t_exec_block *exec, t_pipe *iter_pipe)
{
	change_pipe_fd(exec, iter_pipe);
	set_redirection_fd(exec, CHILD);
	if (exec->command)
	{
		if (is_builtin(exec->command))
			builtin_handler(exec);
		else
			command_handler(exec);
	}
}

void	single_execute(t_exec_block *exec)
{
	pid_t	pid;

	pid = pipe_n_fork(0);
	if (pid == 0)
	{
		set_redirection_fd(exec, CHILD);
		if (exec->command)
			command_handler(exec);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &sys.last_errno, 0);
}

void	execute(t_exec_block *execs)
{
	pid_t			pid;
	t_pipe			iter_pipe;
	t_exec_block	*head;

	iter_pipe.prev_fd = -1;
	head = execs;
	while (head)
	{
		pid = pipe_n_fork(&iter_pipe);
		if (pid == 0)
		{
			child_process(head, &iter_pipe);
			exit(EXIT_SUCCESS);
		}
		close(iter_pipe.prev_fd);
		close(iter_pipe.fd[WRITE]);
		iter_pipe.prev_fd = iter_pipe.fd[READ];
		head = head->next;
	}
	close(iter_pipe.fd[READ]);
	waitpid(pid, &sys.last_errno, 0);
}

void	set_current_cmd(t_exec_block *execs)
{
	t_list	*new_lst;
	char	*data;

	ft_lst_remove_if(&sys.env_lst, "_");
	if (!execs->command || execs->next)
		return ;
	data = ft_strjoin("_=", execs->command);
	new_lst = ft_lstnew(data);
	ft_lstadd_back(&sys.env_lst, new_lst);
}

void	execute_handler(t_exec_block *execs)
{
	if (!execs)
		return ;
	set_current_cmd(execs);
	if (execs->next)
		execute(execs);
	else
	{
		if (is_builtin(execs->command))
		{
			printf("i'm builtin: %s\n", execs->command);
			set_redirection_fd(execs, PARENTS);
			builtin_handler(execs);
		}
		else
			single_execute(execs);
	}
}
