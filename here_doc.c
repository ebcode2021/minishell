/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhong <jinhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:06:31 by jinhong           #+#    #+#             */
/*   Updated: 2022/12/25 23:28:53 by jinhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filename(int number)
{
	char	*str_num;
	char	*tmp_filename;

	str_num = ft_itoa(number);
	tmp_filename = ft_strjoin(".tmp_heredoc", str_num);
	free(str_num);
	return (tmp_filename);
}

char	*expand_quotes(char *input)
{
	char	buffer[BUFFER_SIZE];
	char	opening;
	size_t	i;

	opening = 0;
	i = 0;
	while (input[i])
	{
		if (opening)
		{
			if (input[i] == opening)
				opening = 0;
			else
				buffer[i] = input[i];
		}
		else
		{
			if (input[i] == '\'' || input[i] == '\"')
				opening = input[i];
		}
		i++;
	}
	buffer[i] = 0;
	return (ft_strdup(buffer));
}

void	here_doc(char *eof, char *tmp_filename)
{
	int			fd;
	char		*input;
	const int	eof_len = ft_strlen(eof) + 1;
	const char	*tmp_filename = get_tmp_filename(sys.here_doc_index);

	fd = open(tmp_filename, O_CREATE);
	while (1)
	{
		input = readline(">");
		if (ft_strncmp(input, eof, eof_len) == 0)
		{
			ft_lstadd_back(sys.here_doc_names, tmp_filename);
			free(tmp_filename);
			free(input);
			close(fd);
			return ;
		}
		write(fd, input, ft_strlen(input));
		free(input);
	}
}

void	here_doc_handler(char *raw_input)
{
	size_t	i;
	char	*input;
	char	buffer[BUFFER_SIZE];

	input = expand_quotes(raw_input);
	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' \
			|| input[i] == '|' ||  input[i] == ' ')
			break ;
		buffer[i] == input[i];
		i++;
	}
	buffer[i] = 0;
	here_doc(buffer);
	free(input);
}
