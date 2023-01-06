/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:06:31 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/06 18:53:45 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filename(int number)
{
	char	*str_num;
	char	*tmp_filename;
	char	*tmp;

	str_num = ft_itoa(number);
	tmp = ft_strjoin(g_sys.tmp_dir, "/");
	tmp_filename = ft_strjoin(tmp, str_num);
	free(str_num);
	free(tmp);
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
			if (ft_strncmp(input, eof, eof_len) == 0)
			{
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

char	*quote_handler_without_expand(char *str)
{
	char	buffer[BUFFER_SIZE];
	char	first_quote;
	size_t	str_idx;
	size_t	buf_idx;


	str_idx = 0;
	buf_idx = 0;
	first_quote = 0;
	while (str[str_idx])
	{
		if (!first_quote && (str[str_idx] == '\"' || str[str_idx] == '\''))
			first_quote = str[str_idx];
		else if (str[str_idx] != first_quote)
			buffer[buf_idx++] = str[str_idx];
		str_idx++;
	}
	buffer[buf_idx] = 0;
	return (ft_strdup(buffer));
}

void	here_doc_handler(t_redirecion *redirection)
{
	pid_t		pid;
	char		*tmp_filename;
	extern int	rl_catch_signals;
	char		*replaced;

	tmp_filename = get_tmp_filename(g_sys.here_doc_index++);
	pid = pipe_n_fork(0);
	if (pid == 0)
	{
		rl_catch_signals = 1;
		replaced = quote_handler_without_expand(redirection->file_name);
		here_doc(replaced, tmp_filename);
		free(replaced);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &g_sys.last_exit_status_code, 0);
	child_exit_handler(g_sys.last_exit_status_code);
	free(redirection->file_name);
	redirection->file_name = tmp_filename;
	redirection->type = INFILE;
}
