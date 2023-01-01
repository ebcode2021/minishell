/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2022/12/30 22:03:30 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_ok(char *trimed)
{
	free(trimed);
	return (1);
}

int	raise_syntax_error(char c, char *trimed)
{
	if (c == '\n')
		printf("bash: syntax error near unexpected token `newline\'\n");
	else
		printf("bash: syntax error near unexpected token `%c\'\n", c);
	free(trimed);
	return (0);
}

int	syntax_check(char *input)
{
	int			i;
	const char	*trimed = ft_strtrim(input, " ");

	if (*trimed == '|')
		return (raise_syntax_error('|', (char *)trimed));
	i = -1;
	while (trimed[++i])
	{
		if (trimed[i] == '<' || trimed[i] == '>')
		{
			if (ft_strncmp(trimed + i, "<<", 2) == 0 \
				|| ft_strncmp(trimed + i, ">>", 2) == 0)
				i++;
			else if (ft_strncmp(trimed + i, "<<<", 3) == 0 \
				|| ft_strncmp(trimed + i, ">>>", 3) == 0)
				return (raise_syntax_error(trimed[i], (char *)trimed));
			while (trimed[++i] == ' ')
				i += 0;
			if (!trimed[i])
				return (raise_syntax_error('\n', (char *)trimed));
			else if (trimed[i] == '|' || trimed[i] == '<' || trimed[i] == '>')
				return (raise_syntax_error(trimed[i], (char *)trimed));
		}
		else if (trimed[i] == '|')
		{
			while (trimed[++i] == ' ')
				i += 0;
			if (trimed[i] == '|')
				return (raise_syntax_error(trimed[i], (char *)trimed));
		}
	}
	return (syntax_ok((char *)trimed));
}
