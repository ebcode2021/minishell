/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:22:01 by eunson            #+#    #+#             */
/*   Updated: 2023/01/08 21:13:55 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_replace(char *str, char *to_find, char *to_replace)
{
	size_t	str_idx;
	size_t	buf_idx;
	char	buffer[BUFFER_SIZE];

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

char	*tilde_replace(char *str)
{
	char	buffer[BUFFER_SIZE];
	size_t	buf_idx;
	size_t	str_idx;

	buf_idx = 0;
	str_idx = 0;
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
