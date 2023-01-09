/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:34:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/09 21:42:16 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, size_t *idx)
{
	t_list	*lst;
	char	buffer[BUFFER_SIZE];
	size_t	str_idx;
	size_t	buf_idx;

	str_idx = 1;
	if (idx)
		str_idx += *idx;
	buf_idx = 0;
	while (str[str_idx] && (str[str_idx] != ' ' \
		&& str[str_idx] != '\"' && str[str_idx] != '\'' && str[str_idx] != '|'))
		buffer[buf_idx++] = str[str_idx++];
	buffer[buf_idx] = 0;
	if (idx)
		*idx = str_idx - 1;
	lst = g_sys.env_lst;
	while (lst)
	{
		if (ft_strncmp(buffer, lst->variable_name, buf_idx + 1) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (0);
}

void	expand_env_to_buffer(char *buffer, char *str, size_t *buf_i, size_t *i)
{
	char	*env;

	env = get_env(str, i);
	if (env)
	{
		ft_memcpy(buffer + *buf_i, env, ft_strlen(env));
		*buf_i += ft_strlen(env);
	}
}

char	*expand_env(char *str)
{
	char	buffer[BUFFER_SIZE];
	size_t	str_idx;
	size_t	buf_idx;

	buf_idx = 0;
	if (str)
	{
		str_idx = 0;
		while (str[str_idx])
		{
			if (str[str_idx] == '$')
				expand_env_to_buffer(buffer, str, &buf_idx, &str_idx);
			else if (str[str_idx] != '\"')
				buffer[buf_idx++] = str[str_idx];
			str_idx++;
		}
		free(str);
	}	
	buffer[buf_idx] = 0;
	return (ft_strdup(buffer));
}

char	*quote_handler(char *str)
{
	char	quote;
	char	buffer[BUFFER_SIZE];
	size_t	i;
	size_t	buf_idx;

	i = 0;
	buf_idx = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (quote == '\'')
			buffer[buf_idx++] = str[i];
		else if (quote != '\'' && str[i] == '$')
			expand_env_to_buffer(buffer, str, &buf_idx, &i);
		else
			buffer[buf_idx++] = str[i];
		i++;
	}
	buffer[buf_idx] = 0;
	free(str);
	return (ft_strdup(buffer));
}
