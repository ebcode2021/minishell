/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:35:47 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/08 18:07:54 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_redirecion **head, char **split, size_t *index)
{
	t_redirecion	*block;
	t_redirecion	*new;
	size_t			idx;

	new = ft_calloc(1, sizeof(t_redirecion));
	if (!*head)
		*head = new;
	else
	{
		block = *head;
		while (block->next)
			block = block->next;
		block->next = new;
	}
	idx = *index;
	if (*split[idx] == '<' || *split[idx] == '>')
	{
		new->type = *split[idx++];
		if (*split[idx] == '<' || *split[idx] == '>')
			new->type += *split[idx++];
		new->file_name = ft_strdup(split[idx]);
	}
	*index = idx;
}

char	**set_redirections(t_exec_block *block, char **split)
{
	char	buffer[BUFFER_SIZE];
	size_t	buffer_index;
	size_t	idx;

	idx = 0;
	buffer_index = 0;
	while (split[idx])
	{
		if (*split[idx] == '<' || *split[idx] == '>')
			add_redirection(&block->redirection, split, &idx);
		else
		{
			ft_memcpy(buffer + buffer_index++, " ", 1);
			ft_memcpy(buffer + buffer_index, split[idx], ft_strlen(split[idx]));
			buffer_index += ft_strlen(split[idx]);
		}
		idx++;
	}
	buffer[buffer_index] = 0;
	free_split(split);
	return (split_with_char(buffer, ' '));
}

// char	**set_arguments(char **split)
// {
// 	char	**args;
// 	char	*output;
// 	size_t	idx;
// 	size_t	jdx;

// 	idx = 0;
// 	while (split[idx])
// 		idx++;
// 	args = ft_calloc(idx + 1, sizeof(char *));
// 	idx = 0;
// 	jdx = 0;
// 	while (split[idx])
// 	{
// 		output = quote_handler(split[idx++]);
// 		if (output)
// 			args[jdx++] = output;
// 	}
// 	return (args);
// }

int	is_quoted(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	**lst_to_arr(t_list *lst)
{
	t_list	*elem;
	char	**arr;
	size_t	i;

	arr = ft_malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	elem = lst;
	while (elem)
	{
		arr[i++] = ft_strdup(elem->copy);
		elem = elem->next;
	}
	arr[i] = 0;
	ft_lstclear(&lst, free);
	return (arr);
}

char	**set_arguments(char **split)
{
	t_list	*args;
	char	**expanded;
	size_t	i;
	size_t	j;

	args = 0;
	i = 0;
	while (split[i])
	{
		if (!is_quoted(split[i]))
		{
			j = 0;
			expanded = ft_split(expand_env(tilde_replace(split[i])), ' ');
			while (expanded[j])
				ft_lstadd_back(&args, ft_lstnew(expanded[j++]));
			free_split(expanded);
		}
		else
			ft_lstadd_back(&args, \
			ft_lstnew(quote_handler(split[i])));
		i++;
	}
	return (lst_to_arr(args));
}
