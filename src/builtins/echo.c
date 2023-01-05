/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:00 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 10:49:51 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_exec_block *execs)
{
	size_t	idx;
	int		new_line;

	idx = 1;
	new_line = 1;
	while (execs->args[idx] && ft_strncmp(execs->args[idx], "-n", 3) == 0)
	{
		idx++;
		new_line = 0;
	}
	while (execs->args[idx])
	{
		ft_putstr_fd(execs->args[idx], STDOUT_FILENO);
		if (execs->args[idx++])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (new_line)
		ft_putendl_fd("", STDOUT_FILENO);
}
