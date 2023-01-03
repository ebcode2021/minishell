/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:06:31 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/03 20:39:32 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filename(int number)
{
	char	*str_num;
	char	*tty;
	char	*tmp_filename;

	str_num = ft_itoa(number);
	tty = ttyname(STD_OUT);
	tmp_filename = ft_strjoin(HERE_DOC_DIRECTORY, str_num);
	free(str_num);
	return (tmp_filename);
}

void	here_doc(char *eof, char *tmp_filename)
{
	int			fd;
	char		*input;
	const int	eof_len = ft_strlen(eof) + 1;

	fd = open(tmp_filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		input = readline("> ");
		if (input)
		{
			add_history(input);
			if (ft_strncmp(input, eof, eof_len) == 0)
			{
				ft_lstadd_back(&sys.here_doc_names, \
					ft_lstnew(tmp_filename));
				free(input);
				close(fd);
				return ;
			}
			ft_putendl_fd(input, fd);
			free(input);
		}
		else
			ft_putendl_fd("", fd);
	}
}

int	here_doc_handler(t_redirecion *redirection)
{
	pid_t	pid;
	int		status;
	char	*tmp_filename;

	tmp_filename = get_tmp_filename(sys.here_doc_index++);
	pid = fork();
	if (pid == -1)
	{
		sys.last_errno = errno;
		return (0);
	}
	if (pid == 0)
	{
		here_doc(redirection->file_name, tmp_filename);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	sys.last_exit_status_code = status;
	free(redirection->file_name);
	redirection->file_name = tmp_filename;
	redirection->type = 60;
	return (1);
}
