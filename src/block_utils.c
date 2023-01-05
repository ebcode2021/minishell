/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:33:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 14:33:36 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_exec_block *block)
{
	size_t			i;
	t_redirecion	*elem;

	i = 0;
	ft_putendl_fd("==========================", STDERR_FILENO);
	fprintf(stderr,"cmd: %s\nargs:", block->command);
	while (block->args[i])
		fprintf(stderr,"%s, ", block->args[i++]);
	fprintf(stderr,"\n");
	elem = block->redirection;
	while (elem)
	{
		fprintf(stderr,"file: %s, type: %d\n", \
			elem->file_name, elem->type);
		elem = elem->next;
	}
	ft_putendl_fd("==========================", STDERR_FILENO);
}

t_exec_block	*new_block(void)
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

void	add_block(t_exec_block	**head, t_exec_block *new)
{
	size_t			idx;
	t_exec_block	*block;

	if (!*head)
	{
		*head = new;
		new->idx = 0;
	}
	else
	{
		idx = 0;
		block = *head;
		while (block->next)
		{
			block = block->next;
			idx++;
		}
		block->next = new;
		new->idx = idx + 1;
	}
}

void	free_blocks(t_exec_block *blocks)
{
	t_exec_block	*block;
	t_exec_block	*tmp_block;
	t_redirecion	*r_cur;
	t_redirecion	*r_tmp;

	block = blocks;
	while (block)
	{
		if (block->command)
			free(block->command);
		free_split(block->args);
		r_cur = block->redirection;
		while (r_cur)
		{
			r_tmp = r_cur->next;
			free(r_cur->file_name);
			free(r_cur);
			r_cur = r_tmp;
		}
		tmp_block = block->next;
		free(block);
		block = tmp_block;
	}
}
