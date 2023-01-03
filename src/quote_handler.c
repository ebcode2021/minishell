/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:34:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/03 17:03:10 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, size_t *index)
{
	t_list	*lst;
	char	buffer[BUFFER_SIZE];
	size_t	str_idx;
	size_t	buf_idx;

	str_idx = 1;
	if (index)
		str_idx += *index;
	buf_idx = 0;
	while (str[str_idx] && (str[str_idx] != ' ' || str[str_idx] != -1))
		buffer[buf_idx++] = str[str_idx++];
	buffer[buf_idx] = 0;
	if (index)
		*index = str_idx + 1;
	lst = sys.env_lst;
	while (lst)
	{
		if (ft_strncmp(buffer, lst->variable_name, buf_idx + 1) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (0);
}

char	*expand_env(char *str)
{
	char	buffer[BUFFER_SIZE];
	char	*env;
	size_t	str_idx;
	size_t	buf_idx;

	str_idx = 0;
	buf_idx = 0;
	while (str[str_idx])
	{
		if (str[str_idx] == '$')
		{
			env = get_env(str, &str_idx);
			if (env)
			{
				ft_memcpy(buffer + buf_idx, env, ft_strlen(env));
				buf_idx += ft_strlen(env);
			}
		}
		else if (str[str_idx] != '\"')
			buffer[buf_idx++] = str[str_idx++];
	}
	free(str);
	buffer[buf_idx] = 0;
	return (ft_strdup(buffer));
}

char	*expanded_join(char **split)
{
	char	*tmp;
	char	*expanded;
	char	*result;

	result = ft_calloc(1, 1);
	while (*split)
	{
		expanded = expand_env(*split++);
		tmp = result;
		result = ft_strjoin(tmp, expanded);
		free(tmp);
		free(expanded);
	}
	return (result);
}

char	*double_quote_handler(char *str)
{
	char	**split;
	char	*replaced;

	split = ft_split(str, '\"');
	replaced = expanded_join(split);
	free(split);
	free(str);
	return (replaced);
}

char	*quote_handler(char *str)
{
	char	*result;

	if (ft_strchr(str, '\"'))
		result = double_quote_handler(str);
	else if (ft_strchr(str, '\''))
		result = str_replace(str, "\'", "");
	else
	{
		result = tilde_replace(expand_env(str));
		if (is_blank(result))
		{
			free(result);
			return (0);
		}
	}
	return (result);
}
