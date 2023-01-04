/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:00 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 13:45:13 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_exec_block *execs)
{
	size_t	idx;
	int		n_option;

	//set redirections. but infile does nothing.
	//echo < infile; shoul work the same as just echo;
	idx = 1;
	n_option = 0;
	while (execs->args[idx] && ft_strncmp(execs->args[idx], "-n", 3) == 0)
	{
		idx++;
		n_option = 1;
	}
	while (execs->args[idx])
	{
		ft_putstr_fd(execs->args[idx++], STDOUT_FILENO);
		if (execs->args[idx])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
