/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:30:49 by eunson            #+#    #+#             */
/*   Updated: 2023/01/02 15:04:16 by eunson           ###   ########.fr       */
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

int	get_redirection_fd(t_exec_block *exec)
{
	int	fd;
	
	if (exec->redirection->type == INFILE)
		fd = open(exec->redirection->file_name, O_RDONLY);
	else if (exec->redirection->type == OUTFILE_A)
		fd = open(exec->redirection->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(exec->redirection->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		error_handler();
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	set_redirection_fd(t_exec_block *exec)
{
	int	change_fd;

	while (exec->redirection)
	{
		change_fd = get_redirection_fd(exec);
		if(exec->redirection->type == INFILE)
			dup2(change_fd, STDIN_FILENO);
		else
			dup2(change_fd, STDOUT_FILENO);
		close(change_fd);
		exec->redirection = exec->redirection->next;
	}
}

void	change_io_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	printf("chg_io\n");
	printf("cmd : %s\n", exec->command);
	printf("idx : %zu\n", exec->idx);
	if (iter_pipe)
	{
		printf("iter_pipe 있다.\n");
		if (exec->idx == 0)
		{
			printf("처음");
			dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
		}
		if (exec->next == 0)
		{
			printf("마지막");
			dup2(iter_pipe->prev_fd, STDIN_FILENO);
		}
		if (exec->idx && exec->next)
		{
			printf("중간");
			dup2(iter_pipe->prev_fd, STDIN_FILENO);
			dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
		}
	}
	if (exec->redirection)
		set_redirection_fd(exec);
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
		printf("실행시키는부분\n");
		if (is_builtin(exec->command))
			builtin_handler(exec);
		else
		{
			printf("cmd다.\n");
			command_handler(exec);
		}
	}
}
void	single_execute(t_exec_block *exec)
{
	pid_t	pid;
	
	printf("single_execute\n");
	pid = fork();
	if (pid == 0)
	{
		change_io_fd(exec, 0);
		printf("cmd : %s\n", exec->command);
		if (exec->command)
		{
			printf("여기?????\n");
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
			builtin_handler(execs);
		else
			single_execute(execs);
	}
}
