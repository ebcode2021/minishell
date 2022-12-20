/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:10 by eunson            #+#    #+#             */
/*   Updated: 2022/12/20 19:39:43 by jinholee         ###   ########.fr       */
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

void	builtin_unset(char **to_finds)
{
	size_t	idx;

	idx = 0;
	while (to_finds[idx])
	{
		assert_unset(to_finds[idx]);
		ft_lstremove_if(&sys.envp, to_finds[idx]);
		idx++;
	}
}