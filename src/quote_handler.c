/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:34:57 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/31 00:37:49 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, size_t *index)
{
	t_list	*lst;
	char	buffer[BUFFER_SIZE];
	size_t	i;

	i = *index + 1;
	while (str[i] && str[i] != ' ')
	{
		buffer[i - 1] = str[i];
		i++;
	}
	buffer[i - 1] = 0;
	*index = i;
	lst = sys.env_lst;
	while (lst)
	{
		if (ft_strncmp(buffer, lst->variable_name, i + 1) == 0)
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
		else
			buffer[buf_idx++] = str[str_idx++];
	}
	free(str);
	buffer[buf_idx] = 0;
	return (ft_strdup(buffer));
}

char	*double_quote_handler(char *str)
{
	char	*replaced;

	replaced = str_replace(str, "\"", "");
	replaced = expand_env(replaced);
	return (replaced);
}

char	*single_quote_handler(char *str)
{
	return (str_replace(str, "\'", ""));
}

char	*quote_handler(char *str)
{
	char	*result;

	if (*str == '\"')
		result = double_quote_handler(str);
	else if (*str == '\'')
		result = single_quote_handler(str);
	else
		result = expand_env(str);
	return (result);
}