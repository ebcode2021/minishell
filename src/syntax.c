/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/10 09:18:12 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_blank(char *str, int *idx)
{
	(*idx)++;
	while (str[*idx] && str[*idx] == ' ')
		(*idx)++;
}

static int	close_quote_check(char *str, int *idx, int quote)
{
	(*idx)++;
	if (!str[*idx])
	{
		(*idx)--;
		return (1);
	}
	if (str[*idx] == quote)
		return (0);
	while (str[*idx])
	{
		if (str[*idx] == quote)
			return (0);
		(*idx)++;
	}
	(*idx)--;
	return (1);
}

static int	check_quote(char *str)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (str[idx])
	{
		if (str[idx] == SINGLE_QUOTE || str[idx] == DOUBLE_QUOTE)
			flag = close_quote_check(str, &idx, str[idx]);
		idx++;
	}
	if (flag == 1)
	{
		print_custom_error(str, 0, QUOTE_MATCH);
		return (0);
	}
	return (1);
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

	idx = 0;
	skip_blank(input, &idx);
	if (input[idx] == '|')
		return (syntax_error('|'));
	if (!check_quote(input))
		return (0);
	while (input[++idx])
	{
		if (input[idx] == '<' || input[idx] == '>')
		{
			if (!check_redirection_syntax(input, &idx))
				return (syntax_error(input[idx]));
		}
		else if (input[idx] == '|')
		{
			skip_blank(input, &idx);
			if (!input[idx] || input[idx] == '|')
				return (syntax_error(input[idx]));
			else if (input[idx] == '<' || input[idx] == '>')
				idx--;
		}
	}
	return (1);
}
