/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:39:24 by eunson            #+#    #+#             */
/*   Updated: 2023/01/09 15:21:14 by jinholee         ###   ########.fr       */
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

char	*get_redirection_file_name(char *str)
{
	char	*file_name;
	char	**split;
	size_t	i;

	if (is_quoted(str))
		return (quote_handler(ft_strdup(str)));
	else
	{
		file_name = quote_handler(ft_strdup(str));
		if (file_name)
		{
			split = ft_split(file_name, ' ');
			i = 0;
			while (split[i])
				i++;
			free_split(split);
			if (i > 1)
			{
				free(file_name);
				return (0);
			}
		}
		return (file_name);
	}
}

void	set_redirection_fd(t_exec_block *exec, int child)
{
	int		change_fd;
	char	*file_name;

	while (exec->redirection)
	{
		file_name = get_redirection_file_name(exec->redirection->file_name);
		if (!file_name)
		{
			redirection_error(file_name, exec->redirection->file_name, child);
			break ;
		}
		change_fd = get_redirection_fd(exec, file_name);
		if (change_fd == -1)
		{
			redirection_error(file_name, 0, child);
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
	g_sys.signal = 0;
	dup2(STD_IN, STDIN_FILENO);
	dup2(STD_OUT, STDOUT_FILENO);
}
