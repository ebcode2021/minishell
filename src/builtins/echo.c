/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:00 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 13:26:54 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_exec_block *exec)
{
	size_t	idx;
	int		new_line;

	idx = 1;
	new_line = 1;
	while (exec->args[idx] && ft_strncmp(exec->args[idx], "-n", 3) == 0)
	{
		idx++;
		new_line = 0;
	}
	while (exec->args[idx])
	{
		ft_putstr_fd(exec->args[idx], STDOUT_FILENO);
		if (exec->args[idx++])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (new_line)
		ft_putendl_fd("", STDOUT_FILENO);
}
