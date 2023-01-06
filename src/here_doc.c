/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:06:31 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/06 13:47:49 by jinholee         ###   ########.fr       */
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
			add_history(input);
			if (ft_strncmp(input, eof, eof_len) == 0)
			{
				ft_lstadd_back(&g_sys.here_doc_names, \
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

void	here_doc_handler(t_redirecion *redirection)
{
	pid_t		pid;
	int			status;
	char		*tmp_filename;
	extern int	rl_catch_signals;

	tmp_filename = get_tmp_filename(g_sys.here_doc_index++);
	pid = pipe_n_fork(0);
	if (pid == 0)
	{
		rl_catch_signals = 1;
		here_doc(redirection->file_name, tmp_filename);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	child_exit_handler(status);
	free(redirection->file_name);
	redirection->file_name = tmp_filename;
	redirection->type = INFILE;
}
