/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:37:55 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 13:14:00 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_blank(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*tilde_replace(char *str)
{
	char	buffer[BUFFER_SIZE];
	size_t	str_idx;
	size_t	buf_idx;

	str_idx = 0;
	buf_idx = 0;
	if (ft_strncmp(str, "~", 2) == 0 \
		|| ft_strncmp(str, "~/", 2) == 0)
	{
		ft_memcpy(buffer, g_sys.home_dir, ft_strlen(g_sys.home_dir) + 1);
		buf_idx += ft_strlen(g_sys.home_dir);
		str_idx += 1;
	}
	while (str[str_idx])
		buffer[buf_idx++] = str[str_idx++];
	buffer[buf_idx] = 0;
	free(str);
	return (ft_strdup(buffer));
}

char	*str_replace(char *str, char *to_find, char *to_replace)
{
	char	buffer[BUFFER_SIZE];
	size_t	str_idx;
	size_t	buf_idx;

	str_idx = 0;
	buf_idx = 0;
	while (str[str_idx])
	{
		if (ft_strncmp(str + str_idx, to_find, ft_strlen(to_find)) == 0)
		{
			ft_memcpy(buffer + buf_idx, to_replace, ft_strlen(to_replace));
			str_idx += ft_strlen(to_find);
			buf_idx += ft_strlen(to_replace);
		}
		else
			buffer[buf_idx++] = str[str_idx++];
	}
	buffer[buf_idx] = 0;
	free(str);
	return (ft_strdup(buffer));
}

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

char	**split_with_char(char *raw_input, char c)
{
	char	*converted;
	char	**split;
	char	opening;
	size_t	i;

	converted = ft_strdup(raw_input);
	i = 0;
	opening = 0;
	while (converted[i])
	{
		if (opening)
		{
			if (converted[i] == c)
				converted[i] = -1;
			else if (converted[i] == opening)
				opening = 0;
		}
		else if (converted[i] == '\'' || converted[i] == '\"')
			opening = converted[i];
		i++;
	}
	split = ft_split(converted, c);
	convert_back(split, c);
	free(converted);
	return (split);
}
