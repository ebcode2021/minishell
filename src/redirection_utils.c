/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:35:47 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/02 18:12:52 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_redirecion **head, char **split, size_t *index)
{
	t_redirecion	*block;
	t_redirecion	*new;
	size_t			i;

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
	i = *index;
	if (*split[i] == '<' || *split[i] == '>')
	{
		new->type = *split[i++];
		if (*split[i] == '<' || *split[i] == '>')
			new->type += *split[i++];
		new->file_name = ft_strdup(split[i]);
	}
	*index = i;
}

char	**set_redirections(t_exec_block *block, char **split)
{
	char	buffer[BUFFER_SIZE];
	size_t	buffer_index;
	size_t	i;

	i = 0;
	buffer_index = 0;
	while (split[i])
	{
		if (*split[i] == '<' || *split[i] == '>')
			add_redirection(&block->redirection, split, &i);
		else
		{
			ft_memcpy(buffer + buffer_index++, " ", 1);
			ft_memcpy(buffer + buffer_index, split[i], ft_strlen(split[i]));
			buffer_index += ft_strlen(split[i]);
		}
		i++;
	}
	buffer[buffer_index] = 0;
	free_split(split);
	return (split_with_char(buffer, ' '));
}

char	**set_arguments(char **split)
{
	char	**args;
	char	*output;
	size_t	i;
	size_t	j;

	i = 0;
	while (split[i])
		i++;
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (split[i])
	{
		output = quote_handler(split[i++]);
		if (output)
			args[j++] = output;
	}
	return (args);
}
