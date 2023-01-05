/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/05 20:58:15 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_blank(char *str, int *idx)
{
	(*idx)++;
	while (str[*idx] && str[*idx] == ' ')
		(*idx)++;
}

static int	check_redirection_syntax(char *str, int *idx)
{
	char	*location;

	location = str + *idx;
	if (!ft_strncmp(location, "<<", 2) || !ft_strncmp(location, ">>", 2))
		(*idx)++;
	else if (!ft_strncmp(location, "<<<", 3) || !ft_strncmp(location, ">>>", 3))
		return (0);
	skip_blank(str, idx);
	if (!str[*idx] || str[*idx] == '|' || str[*idx] == '<' || str[*idx] == '>')
		return (0);
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
			if (!check_redirection_syntax((char *)trimed, &idx))
				return (syntax_error(trimed[idx], (char *)trimed));
		}
		else if (trimed[idx] == '|')
		{
			skip_blank((char *)trimed, &idx);
			if (!trimed[idx] || trimed[idx] == '|')
				return (syntax_error(trimed[idx], (char *)trimed));
			else if (trimed[idx] == '<' || trimed[idx] == '>')
				idx--;
		}
	}
	free((char *)trimed);
	return (1);
}
