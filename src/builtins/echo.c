/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:00 by eunson            #+#    #+#             */
/*   Updated: 2023/01/01 20:13:14 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_exec_block block)
{
	size_t	i;
	int		fd;
	int		n_option;

	//set redirections. but infile does nothing.
	//echo < infile; shoul work the same as just echo;
	i = 0;
	n_option = 0;
	while (block->args[i] && ft_strncmp(block->args[i], "-n", 3) == 0)
		i++;
	while (block->args[i])
	{
		ft_putstr_fd(block->args[i], fd);
	}
	if (!n_option)
		ft_putchar_fd('\n', fd);
}
