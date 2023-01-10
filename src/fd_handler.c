/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:39:24 by eunson            #+#    #+#             */
/*   Updated: 2023/01/10 14:14:44 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_fd(t_redirecion *redirection, char *file_name)
{
	int	fd;

	if (redirection->type == INFILE)
		fd = open(file_name, O_RDONLY);
	else if (redirection->type == OUTFILE_A)
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

	file_name = quote_handler(ft_strdup(str));
	if (!is_quoted(str))
	{
		if (is_blank(file_name))
		{
			free(file_name);
			return (0);
		}
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

void	set_redirection_fd(t_exec_block *execs, int child)
{
	t_redirecion	*redirection;
	int				change_fd;
	char			*file_name;

	redirection = execs->redirection;
	while (redirection)
	{
		file_name = get_redirection_file_name(redirection->file_name);
		if (!file_name)
			return (redirection_error(file_name, \
					redirection->file_name, child));
		change_fd = get_redirection_fd(redirection, file_name);
		if (change_fd == -1)
			return (redirection_error(file_name, 0, child));
		if (redirection->type == INFILE)
			dup2(change_fd, STDIN_FILENO);
		else
			dup2(change_fd, STDOUT_FILENO);
		close(change_fd);
		free(file_name);
		redirection = redirection->next;
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

void	reset_params(void)
{
	g_sys.signal = 0;
	g_sys.here_doc_index = 0;
	dup2(STD_IN, STDIN_FILENO);
	dup2(STD_OUT, STDOUT_FILENO);
}
