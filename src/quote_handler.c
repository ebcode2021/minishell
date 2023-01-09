/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:34:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/09 20:50:29 by jinholee         ###   ########.fr       */
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

void	expand_env_to_buffer(char *buffer, char *str, size_t *buf_idx, size_t *i)
{
	char	*env;

	env = get_env(str, i);
	if (env)
	{
		ft_memcpy(buffer + *buf_idx, env, ft_strlen(env));
		*buf_idx += ft_strlen(env);
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

// char	*expanded_join(char **split)
// {
// 	char	*tmp;
// 	char	*expanded;
// 	char	*result;

// 	result = ft_calloc(1, 1);
// 	while (*split)
// 	{
// 		expanded = expand_env(*split++);
// 		tmp = result;
// 		result = ft_strjoin(tmp, expanded);
// 		free(tmp);
// 		free(expanded);
// 	}
// 	return (result);
// }

// char	*double_quote_handler(char *str)
// {
// 	char	**split;
// 	char	*replaced;

// 	split = ft_split(str, '\"');
// 	replaced = expanded_join(split);
// 	free(split);
// 	free(str);
// 	return (replaced);
// }

// char	*quote_handler(char *str)
// {
// 	char	*result;
// 	char	first_quote;
// 	size_t	idx;

// 	first_quote = 0;
// 	idx = 0;
// 	while (str[idx])
// 	{
// 		if (str[idx] == '\'' || str[idx] == '\"')
// 			first_quote = str[idx];
// 		idx++;
// 	}
// 	if (first_quote == '\"')
// 		result = double_quote_handler(str);
// 	else if (first_quote == '\'')
// 		result = str_replace(str, "\'", "");
// 	else
// 	{
// 		result = expand_env(tilde_replace(str));
// 		if (is_blank(result))
// 		{
// 			free(result);
// 			return (0);
// 		}
// 	}
// 	return (result);
// }
