/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:06:31 by jinhong           #+#    #+#             */
/*   Updated: 2022/12/26 15:34:31 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filename(int number)
{
	char	*str_num;
	char	*tmp_filename;

	str_num = ft_itoa(number);
	tmp_filename = ft_strjoin(HERE_DOC_DIRECTORY, str_num);
	printf("here_doc name : %s\n", tmp_filename);
	free(str_num);
	return (tmp_filename);
}

char	*expand_quotes(char *input)
{
	char	buffer[BUFFER_SIZE];
	char	opening;
	size_t	input_index;
	size_t	buffer_index;

	opening = 0;
	input_index = 0;
	buffer_index = 0;
	while (input[input_index])
	{
		if (opening && input[input_index] == opening)
			opening = 0;
		else if (!opening \
			&& (input[input_index] == '\'' || input[input_index] == '\"'))
			opening = input[input_index];
		else
			buffer[buffer_index++] = input[input_index];
		input_index++;
	}
	buffer[buffer_index] = 0;
	return (ft_strdup(buffer));
}

void	here_doc(char *eof, char *tmp_filename)
{
	int			fd;
	char		*input;
	const int	eof_len = ft_strlen(eof) + 1;

	fd = open(tmp_filename, O_CREAT);
	while (1)
	{
		input = readline("> ");
		add_history(input);
		if (ft_strncmp(input, eof, eof_len) == 0)
		{
			ft_lstadd_back(&sys.here_doc_names, \
				ft_lstnew((char *)tmp_filename, ""));
			free(input);
			close(fd);
			return ;
		}
		write(fd, input, ft_strlen(input));
		free(input);
	}
}

void	here_doc_handler(char *raw_input, char *tmp_filename)
{
	size_t	input_index;
	size_t	buffer_index;
	char	*input;
	char	buffer[BUFFER_SIZE];

	input = expand_quotes(raw_input);
	input_index = 0;
	buffer_index = 0;
	while (input[input_index] == ' ')
		input_index++;
	while (input[input_index])
	{
		if (input[input_index] == '<' || input[input_index] == '>' \
			|| input[input_index] == '|' || input[input_index] == ' ')
			break ;
		buffer[buffer_index++] = input[input_index++];
	}
	buffer[buffer_index] = 0;
	here_doc(buffer, tmp_filename);
	free(input);
}

int	here_doc_fork(char *raw_input)
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
		printf("child process doing here_doc...\n");
		here_doc_handler(raw_input, tmp_filename);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	sys.last_exit_status_code = status;
	free((char *)tmp_filename);
	return (1);
}
