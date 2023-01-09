/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:33:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/09 11:55:28 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
