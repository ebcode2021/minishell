/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:39:24 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 10:53:38 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_fd(t_exec_block *exec, char *file_name)
{
	int	fd;

	if (exec->redirection->type == INFILE)
		fd = open(file_name, O_RDONLY);
	else if (exec->redirection->type == OUTFILE_A)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

void	set_redirection_fd(t_exec_block *exec, int child)
{
	int		change_fd;
	char	*file_name;

	while (exec->redirection)
	{
		file_name = quote_handler(ft_strdup(exec->redirection->file_name));
		if (!file_name)
		{
			redirection_error(file_name, child);
			break ;
		}
		change_fd = get_redirection_fd(exec, file_name);
		if (change_fd == -1)
		{
			redirection_error(file_name, child);
			break ;
		}
		if (exec->redirection->type == INFILE)
			dup2(change_fd, STDIN_FILENO);
		else
			dup2(change_fd, STDOUT_FILENO);
		close(change_fd);
		free(file_name);
		exec->redirection = exec->redirection->next;
	}
}

void	change_pipe_fd(t_exec_block *exec, t_pipe *iter_pipe)
{
	if (iter_pipe)
	{
		if (exec->idx == 0)
			dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
		if (exec->next == 0)
			dup2(iter_pipe->prev_fd, STDIN_FILENO);
		if (exec->idx && exec->next)
		{
			dup2(iter_pipe->prev_fd, STDIN_FILENO);
			dup2(iter_pipe->fd[WRITE], STDOUT_FILENO);
		}
	}
	close(iter_pipe->fd[READ]);
	close(iter_pipe->fd[WRITE]);
	close(iter_pipe->prev_fd);
}

void	reset_fd(void)
{
	dup2(STDIN_FILENO, STD_IN);
	dup2(STDOUT_FILENO, STD_OUT);
}
