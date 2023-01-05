/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/05 13:46:39 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *trimed)
{
	free(trimed);
	return (1);
}

static int	raise_syntax_error(char c, char *trimed)
{
	if (c == '\n')
		fprintf(stderr,"picoshell: syntax error near unexpected token `newline\'\n");
	else
		fprintf(stderr,"picoshell: syntax error near unexpected token `%c\'\n", c);
	free(trimed);
	return (0);
}

int	syntax_check(char *input)
{
	int			idx;
	const char	*trimed = ft_strtrim(input, " ");

	if (*trimed == '|')
		return (raise_syntax_error('|', (char *)trimed));
	idx = -1;
	while (trimed[++idx])
	{
		if (trimed[idx] == '<' || trimed[idx] == '>')
		{
			if (ft_strncmp(trimed + idx, "<<", 2) == 0 \
				|| ft_strncmp(trimed + idx, ">>", 2) == 0)
				idx++;
			else if (ft_strncmp(trimed + idx, "<<<", 3) == 0 \
				|| ft_strncmp(trimed + idx, ">>>", 3) == 0)
				return (raise_syntax_error(trimed[idx], (char *)trimed));
			while (trimed[++idx] == ' ')
				idx += 0;
			if (!trimed[idx])
				return (raise_syntax_error('\n', (char *)trimed));
			else if (trimed[idx] == '|' || trimed[idx] == '<' || trimed[idx] == '>')
				return (raise_syntax_error(trimed[idx], (char *)trimed));
		}
		else if (trimed[idx] == '|')
		{
			while (trimed[++idx] == ' ')
				idx += 0;
			if (trimed[idx] == '|')
				return (raise_syntax_error(trimed[idx], (char *)trimed));
		}
	}
	return (check_syntax((char *)trimed));
}
