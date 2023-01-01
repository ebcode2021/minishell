/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:30:49 by eunson            #+#    #+#             */
/*   Updated: 2023/01/01 19:01:11 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipe
{
	int	fd[2];
	int	prev_fd;
}				t_pipe;

// pipe -> fd[READ], fd[WRITE]
# define READ 0
# define WRITE 1

// redirection.type
# define DEFULAT 0
# define INFILE 1
# define HERE_DOC 2
# define OUTFILE_APPEND 3
# define OUTFILE_TRUNC 4

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
	else if (exec->redirection->type == OUTFILE_APPEND)
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

void	set_redirection_fd(t_exec_block *exec, int current_fd[2])
{
	int	change_fd;

	while (exec->redirection)
	{
		change_fd = get_redirection_fd(exec);
		if(exec->redirection->type == INFILE)
			current_fd[STDIN_FILENO] = change_fd;
		else
			current_fd[STDOUT_FILENO] = change_fd;
		exec->redirection = exec->redirection->next;
	}
}

void	change_io_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	int	current_fd[2];

	current_fd[READ] = STDIN_FILENO;
	current_fd[WRITE] = STDOUT_FILENO;
	if (iter_pipe)
	{
		if (exec->idx == 0)
			//처음
		if (exec->next == 0)
			//마지막
		if (exec->idx && exec->next)
			//중간
	}
	if (exec->redirection)
		set_redirection_fd(exec, current_fd);
}

void	child_process(t_exec_block *exec, t_pipe *iter_pipe)
{
	change_io_fd(exec, iter_pipe);
	close(iter_pipe->fd[READ]);
	close(iter_pipe->fd[WRITE]);
	close(iter_pipe->prev_fd);
	if (exec->command)
	{
		if (is_builtin(exec->command))
			builtin_handler(exec);
		else
			command_handler(exec);
	}
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
	pid_t	pid;

	if (execs->next) //2개 이상일 때
		execute(execs); 
	else //1개 일때
	{
		if (is_builtin(execs->command))
			builtin_handler(execs);
		else
			execute(execs);
	}
}