/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/05 14:26:30 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_syntax(char *trimed)
{
	free(trimed);
	return (1);
}

int	syntax_check(char *input)
{
	int			idx;
	const char	*trimed = ft_strtrim(input, " ");

	if (*trimed == '|')
		return (syntax_error('|', (char *)trimed));
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
				return (syntax_error(trimed[idx], (char *)trimed));
			while (trimed[++idx] == ' ')
				continue ;
			if (!trimed[idx])
				return (syntax_error('\n', (char *)trimed));
			else if (trimed[idx] == '|' || trimed[idx] == '<' || trimed[idx] == '>')
				return (syntax_error(trimed[idx], (char *)trimed));
		}
		else if (trimed[idx] == '|')
		{
			while (trimed[++idx] == ' ')
				continue ;
			if (trimed[idx] == '|')
				return (syntax_error(trimed[idx], (char *)trimed));
		}
	}
	return (is_syntax((char *)trimed));
}
