/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:04:05 by jinhong           #+#    #+#             */
/*   Updated: 2023/01/10 13:15:39 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_blank(char *str, size_t *idx)
{
	size_t	i;

	i = *idx;
	while (str[i] == ' ')
		i++;
	*idx = i;
}

void	skip_quote(char *str, size_t *idx, char quote)
{
	size_t	i;

	i = *idx + 1;
	while (str[i] && str[i] != quote)
		i++;
	*idx = i + 1;
}

int	first_check(char *str, size_t *idx)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		i++;
	}
	if (quote)
	{
		print_custom_error(str, 0, QUOTE_MATCH);
		return (0);
	}
	i = 0;
	skip_blank(str, &i);
	if (str[i] == '|')
		return (syntax_error(str[i]));
	*idx = i;
	return (1);
}

int	check_redirection_syntax(char *str, size_t *idx)
{
	char	*location;

	location = str + *idx;
	if (!ft_strncmp(location, "<<", 2) || !ft_strncmp(location, ">>", 2))
		*idx += 2;
	else
		*idx += 1;
	skip_blank(str, idx);
	if (!str[*idx] || str[*idx] == '|' || str[*idx] == '<' || str[*idx] == '>')
		return (0);
	*idx += 1;
	return (1);
}

int	syntax_check(char *input)
{
	size_t	i;

	i = 0;
	if (!first_check(input, &i))
		return (0);
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (!check_redirection_syntax(input, &i))
				return (syntax_error(input[i]));
		}
		else if (input[i] == '\'' || input[i] == '\"')
			skip_quote(input, &i, input[i]);
		else if (input[i] == '|' && (i++))
		{
			skip_blank(input, &i);
			if (!input[i] || input[i] == '|')
				return (syntax_error(input[i]));
		}
		else
			i++;
	}
	return (1);
}
