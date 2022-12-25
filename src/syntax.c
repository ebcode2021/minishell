/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhong <jinhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2022/12/25 15:49:44 by jinhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	raise_syntax_error(char c)
{
	if (c == '\n')
		printf("bash: syntax error near unexpected token `newline\'\n");
	else
		printf("bash: syntax error near unexpected token `%c\'\n", c);
	exit(1);
}

void	syntax_check(char *input)
{
	int			i;
	const char	*trimed = ft_strtrim(input, " ");

	if (*trimed == '|')
		raise_syntax_error('|');
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
				raise_syntax_error(trimed[i]);
			while (trimed[++i] == ' ')
				i += 0;
			if (!trimed[i])
				raise_syntax_error('\n');
			else if (trimed[i] == '|' || trimed[i] == '<' || trimed[i] == '>')
				raise_syntax_error(trimed[i]);
		}
	}
	free((char *)trimed);
}
