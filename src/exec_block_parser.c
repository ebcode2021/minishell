/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:44:34 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/29 12:29:51 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_block	*block_new()
{
	t_exec_block	*new;

	new = malloc(sizeof(t_exec_block));
	if (new)
	{
		new->command = 0;
		new->args = 0;
		new->redirection = 0;
		new->next = 0;
	}
	return (new);
}

void	block_add(t_exec_block	**head, t_exec_block *new)
{
	t_exec_block	*block;

	if (!*head)
		*head = new;
	else
	{
		block = *head;
		while (block->next)
			block = block->next;
		block->next = new;
	}
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
		{
			buffer[buf_idx++] = str[str_idx++];
		}
	}
	buffer[buf_idx] = 0;
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

void	add_redirection(t_redirecion **head, char **split, size_t *index)
{
	t_redirecion	*elem;
	size_t			i;

	if (!*head)
	{
		*head = malloc(sizeof(t_redirecion));
		elem = *head;
		elem->next = 0;
	}
	else
		elem = *head;
	while (elem->next)
		elem = elem->next;
	elem->next = malloc(sizeof(t_redirecion));
	elem = elem->next;
	i = *index;
	if (*split[i] == '<' || *split[i] == '>')
	{
		elem->type = *split[i++];
		if (*split[i] == '<' || *split[i] == '>')
			elem->type += *split[i++];
		elem->file_name = split[i];
	}
	*index = i;
}

char	**set_redirections(t_exec_block *block, char **split)
{
	char	*replaced;
	char	*tmp;
	size_t	i;

	replaced = ft_calloc(1,1);
	i = 0;
	while (split[i])
	{
		if (*split[i] == '<' || *split[i] == '>')
			add_redirection(&block->redirection, split, &i);
		else
		{
			tmp = ft_strjoin(replaced, split[i]);
			free(replaced);
			replaced = tmp;
		}
		i++;
	}
	while (block->redirection)
	{
		printf("file :%s, type:%d\n", block->redirection->file_name, block->redirection->type);
		block->redirection = block->redirection->next;
	}
	return (ft_split(replaced, ' '));
}

t_exec_block	*str_to_block(char *str)
{
	t_exec_block	*block;
	char			*replaced;
	char			**split;

	block = block_new();
	replaced = str_replace(str, "<", " < ");
	str = str_replace(replaced, ">", " > ");
	printf("replaced : %s\n", str);
	free(replaced);
	split = split_with_char(str, ' ');
	split = set_redirections(block, split);
	block->args = split;
	block->command = ft_strdup(block->args[0]);
	// while (block->redirection)
	// {
	// 	printf("file :%s, type:%d\n", block->redirection->file_name, block->redirection->type);
	// 	block->redirection = block->redirection->next;
	// }
	return (block);
}

void	exec_block_parser(char *raw_input)
{
	char			**pipe_split;
	t_exec_block	*exec_blocks;
	size_t			i;

	i = 0;
	exec_blocks = 0;
	pipe_split = split_with_char(raw_input, '|');
	while (pipe_split[i])
		block_add(&exec_blocks, str_to_block(pipe_split[i++]));
	free_split(pipe_split); 
}
