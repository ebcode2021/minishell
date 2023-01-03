/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:30:49 by eunson            #+#    #+#             */
/*   Updated: 2023/01/03 09:47:08 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pipe_n_fork(t_pipe *new_pipe)
{
	pid_t	pid;

	pipe(new_pipe->fd);
	pid = fork();
	if (pid == -1)
		error_handler();
	return (pid);
}

void	child_process(t_exec_block *exec, t_pipe *iter_pipe)
{
	change_io_fd(exec, iter_pipe);
	if (iter_pipe)
	{
		close(iter_pipe->fd[READ]);
		close(iter_pipe->fd[WRITE]);
		close(iter_pipe->prev_fd);
	}
	if (exec->command)
	{
		fprintf(stderr,"실행시키는부분\n");
		if (is_builtin(exec->command))
			builtin_handler(exec);
		else
		{
			fprintf(stderr,"cmd다.\n");
			command_handler(exec);
		}
	}
}
void	single_execute(t_exec_block *exec)
{
	pid_t	pid;
	
	fprintf(stderr,"single_execute\n");
	pid = fork();
	if (pid == 0)
	{
		change_io_fd(exec, 0);
		fprintf(stderr,"cmd : %s\n", exec->command);
		if (exec->command)
		{
			fprintf(stderr,"여기?????\n");
			command_handler(exec);
		}
	}
	else if (pid == -1)
		error_handler();
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
			break ;
		}
		close(iter_pipe.prev_fd);
		close(iter_pipe.fd[WRITE]);
		iter_pipe.prev_fd = iter_pipe.fd[READ];
		head = head->next;
	}
	close(iter_pipe.fd[READ]);
	waitpid(pid, &sys.last_errno, 0);
}

void	execute_handler(t_exec_block *execs)
{
	if (execs->next)
		execute(execs); 
	else
	{
		if (is_builtin(execs->command))
			builtin_handler(execs);// builtin을 parent에서 하니까 그냥 exit하면 안됨.
		else
			single_execute(execs);
	}
}
