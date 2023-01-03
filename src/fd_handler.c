/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:39:24 by eunson            #+#    #+#             */
/*   Updated: 2023/01/03 12:00:24 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fd(void)
{
	dup2(STD_IN, STDIN_FILENO);
	dup2(STD_OUT, STDOUT_FILENO);
}

int	get_redirection_fd(t_exec_block *exec, int parents)
{
	int		fd;
	char	*file_name;

	file_name = quote_handler(exec->redirection->file_name);
	if (!file_name)
		error_handler(exec, REDIRECTION, 0);
	if (exec->redirection->type == INFILE)
		fd = open(exec->redirection->file_name, O_RDONLY);
	else if (exec->redirection->type == OUTFILE_A)
		fd = open(exec->redirection->file_name, \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(exec->redirection->file_name, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		error_handler(exec, REDIRECTION, parents);
	return (fd);
}

void	set_redirection_fd(t_exec_block *exec, int parents)
{
	int	change_fd;

	while (exec->redirection)
	{
		change_fd = get_redirection_fd(exec, parents);
		if (exec->redirection->type == INFILE)
			dup2(change_fd, STDIN_FILENO);
		else
			dup2(change_fd, STDOUT_FILENO);
		close(change_fd);
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
