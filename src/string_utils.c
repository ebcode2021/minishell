/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:37:55 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 14:14:04 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_back(char **split, char c)
{
	char	*str;

	while (*split)
	{
		str = *split++;
		while (*str)
		{
			if (*str == -1)
				*str = c;
			str++;
		}
	}
}

int	is_blank(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] != ' ')
			return (0);
		idx++;
	}
	return (1);
}

char	**split_with_char(char *raw_input, char c)
{
	char	*converted;
	char	**split;
	char	opening;
	size_t	idx;

	converted = ft_strdup(raw_input);
	idx = 0;
	opening = 0;
	while (converted[idx])
	{
		if (opening)
		{
			if (converted[idx] == c)
				converted[idx] = -1;
			else if (converted[idx] == opening)
				opening = 0;
		}
		else if (converted[idx] == '\'' || converted[idx] == '\"')
			opening = converted[idx];
		idx++;
	}
	split = ft_split(converted, c);
	convert_back(split, c);
	free(converted);
	return (split);
}

void	free_split(char **splitted)
{
	size_t	idx;

	idx = 0;
	while (splitted[idx])
		free(splitted[idx++]);
	free(splitted);
}

void	*ft_malloc(size_t size)
{
	void	*mem;

	mem = ft_calloc(1, size);
	if (!mem)
	{
		print_custom_error(0, 0, MALLOC_FAIL);
		exit(EXIT_FAILURE);
	}
	return (mem);
}
