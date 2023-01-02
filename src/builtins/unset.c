/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:10 by eunson            #+#    #+#             */
/*   Updated: 2023/01/01 20:30:57 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assert_unset(char *to_find)
{
	size_t	idx;

	idx = 0;
	if (!(ft_isalpha(to_find[idx]) || \
		to_find[idx] == '_' || to_find[idx] == '*'))
		error_handler();
		//bash: unset: `1': not a valid identifier
	idx = 1;
	while (to_find[idx])
	{
		if (to_find[idx] != '_'	&& !ft_isalnum(to_find[idx]))
		{
			error_handler();
			break ;
		}
		idx++;
	}	
}

void	builtin_unset(t_exec_block block)
{
	size_t	idx;
	char	**to_finds;

	to_finds = block->args;
	idx = 0;
	while (to_finds[idx])
	{
		assert_unset(to_finds[idx]);
		//maybe...assert function should return a value to make
		//if else condition. But since there is no chance of finding
		//a invalid identifier, there's only a bit of ineffictioncy
		//and whould still work fine.
		ft_lstremove_if(&sys.envp, to_finds[idx]);
		idx++;
	}
}