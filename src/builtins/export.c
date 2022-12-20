/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:06 by eunson            #+#    #+#             */
/*   Updated: 2022/12/20 16:51:32 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assert_export(char *arg)
{
	char	*sign_idx;

	sign_idx = ft_strchr(args[i], '=')		
	if (!sign_idx || sign_idx == args[i] || ft_isdigit(*args[i]))
	{
		error_handler()
	}
}

void	builtin_export(t_system *sys, char **args)
{
	char	*splitted;
	char	*variable_name;
	char	*value;
	size_t	idx;

	if (!*args)
	{
		//단순 프린트(declare -x + 정렬 시간나면)
	}
	idx = 0;
	while (args[idx])
	{
		assert_export(args[idx]);
		splitted = ft_split(args[idx], '=');
		variable_name = splitted[0];
		value = splitted[1];
		if (!value)
			value = "";
		ft_lstadd_back(&sys->env_list, ft_lstnew(variable_name, value));
		free_split(splitted);
		idx++;
	}
}

command = export Q=1 W= 2
ft_split(command, ' ') -> ['export', 'Q=1', 'W=', '2', 0]
biultin_export(system, spliited + 1)
