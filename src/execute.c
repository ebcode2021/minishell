/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:33:54 by eunson            #+#    #+#             */
/*   Updated: 2023/01/01 16:10:39 by eunson           ###   ########.fr       */
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
	// <asds | <tmp1 >outfile 
	// cmd <infile >outfile export a=2
	// export 1=2
	// cat 
	// < ctrl+c
	
	

	if (exec->redirection)  //redirection이 있을 때랑, 없을 때로 나뉘지 않을까?
		set_redirection_fd(exec, current_fd);
	else
	{
		
	}
	if (exec->command && iter_pipe)
	{
		
	}
	else if (exec->command && !iter_pipe)
	{
		
	}
}

void	change_io_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	int	stdin_fd;
	int	stdout_fd;
	int	change_fd;

	stdin_fd = STDIN_FILENO;
	stdout_fd = STDOUT_FILENO;
	while (exec->redirection)
	{
		change_fd = get_redirection_fd(exec);
		if (exec->redirection->type == INFILE)
			stdin_fd = change_fd;
		else
			stdout_fd = change_fd;
		exec->redirection = exec->redirection->next;
	}
	if (exec->idx == 0)
	{
		// 처음
		// 마지막
		// 중간
	}
	else if (exec->next == 0)
	{
		
	}
	else
	{
		
	}
}

void	change_io_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	int change_fd;
	
	while (exec->redirection)
	{
		change_fd = get_redirection_fd(exec);
		if (change_fd == -1)
		{
			error_handler();
			continue;
		}
		if (exec->redirection->type == INFILE)
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
		exec->redirection = exec->redirection->next;
	}
	if (exec->command)
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
	if (exec->command)
	{
		if (is_builtin(exec->command))
			builtin_handler(exec); //built_in..
			//export 1=a | export 2=b | export 3=c
			
			// signal->bash..? 
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
	if (head->next)
	{
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
	else
	{
		change_io_fd(execs, 0); //<infile >outfile
		execute_cmd(execs); //builtin , cmd
	}
}
