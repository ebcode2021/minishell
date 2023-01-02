/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:44:34 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/02 15:50:49 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_block	*str_to_block(char *str)
{
	t_exec_block	*block;
	t_redirecion	*elem;
	char			*replaced;
	char			**split;

	block = block_new();
	replaced = str_replace(str, "<", " < ");
	replaced = str_replace(replaced, ">", " > ");
	split = set_redirections(block, split_with_char(replaced, ' '));
	block->args = set_arguments(split);
	if (block->args[0])
		block->command = ft_strdup(block->args[0]);
	elem = block->redirection;
	while (elem)
	{
		if (elem->type == HERE_DOC)
			here_doc_handler(elem);
		elem = elem->next;
	}
	print_block(block);
	free(replaced);
	free(split);
	return (block);
}

t_exec_block *exec_block_parser(char *raw_input)
{
	char			**pipe_split;
	t_exec_block	*exec_blocks;
	size_t			i;

	i = 0;
	exec_blocks = 0;
	pipe_split = split_with_char(raw_input, '|');
	while (pipe_split[i])
		block_add(&exec_blocks, str_to_block(pipe_split[i++]));
	free(pipe_split);
	return (exec_blocks);
}
