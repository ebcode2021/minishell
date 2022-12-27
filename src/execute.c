/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:33:54 by eunson            #+#    #+#             */
/*   Updated: 2022/12/27 13:22:48 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// syntac_check -> parsing -> execute 가정
// main에서 t_exect_block execs;
// if (syntax_check(input))
// {
// 	parsing(&execs)
// 	execute(&execs)
// }
// free_execs_block(execs)

typedef struct s_pipe
{
	int	fd[2];
	int	prev_fd;
}				t_pipe;

# define READ 0
# define WRITE 1

// redirection.type
# define DEFULAT 0
# define INFILE 1
# define OUTFILE_APPEND 2
# define OUTFILE_TRUNC 3

pid_t	pipe_n_fork(t_pipe *new_pipe)
{
	pid_t	pid;

	pipe(new_pipe->fd);
	pid = fork();
	if (pid == -1)
		error_handler();
	return (pid);
}

int	redirection_handler(t_exec_block *exec)
{
	int	change_fd;
	
	if (exec->redirection.type == INFILE)
		change_fd = open(exec->redirection.file_name, O_RDONLY);
	else if (exec->redirection.type == OUTFILE_APPEND)
		change_fd = open(exec->redirection.file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		change_fd = open(exec->redirection.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (change_fd == -1)
		error_handler();
	return (change_fd);
}

void	change_io_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	int change_fd;

	if (exec->redirection.file_name)
	{
		change_fd = redirection_handler(exec);
		if (exec->redirection.type == INFILE)
		{
			dup2(change_fd, STDIN_FILENO);
			dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
		}
		else
		{
			dup2(change_fd, STDOUT_FILENO);
			dup2(iter_pipe->fd[READ], STDIN_FILENO);
		}
		close(change_fd);
	}
	else
	{
		dup2(iter_pipe->prev_fd, STDIN_FILENO);
		dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
	}
}

void	child_process(t_exec_block *exec, t_pipe *iter_pipe)
{
	change_io_fd(exec, iter_pipe);
	close(iter_pipe->fd[READ]);
	close(iter_pipe->fd[WRITE]);
	close(iter_pipe->prev_fd);
	if (is_builtin(exec->command))
		builtin_handler(exec);
	else
		command_handler(exec);
}

void	execute(t_exec_block *execs)
{
	pid_t	pid;
	t_pipe	iter_pipe;
	t_exec_block	*head;

	iter_pipe.prev_fd = -1;
	head = execs;
	while (head)
	{
		pid = pipe_n_fork(&iter_pipe);
		if (pid == 0)
		{
			child_process(head, &iter_pipe);
			break;
		}
		close(iter_pipe.prev_fd);
		close(iter_pipe.fd[WRITE]);
		iter_pipe.prev_fd = iter_pipe.fd[READ];
		head = head->next;
	}
	close(iter_pipe.fd[READ]);
	waitpid(pid, &sys.last_exit_status_code, 0);
}