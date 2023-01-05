/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 10:47:54 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_long(char *str)
{
	int				sign;
	int				flag;
	unsigned long	temp;

	temp = 0;
	flag = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		flag = 1;
		temp = temp * 10 + (*str++ - '0');
		if (temp > LONG_MAX || (temp == LONG_MAX + 1 && sign != -1))
			return (0);
	}
	return (flag);
}

void	builtin_exit(t_exec_block *execs)
{
	int		exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (execs->args[1])
	{
		if (is_long(execs->args[1]))
			exit_code = ft_atoi(execs->args[1]);
		else
		{
			print_custom_error(execs->command, execs->args[1], NUMERIC_ARG);
			exit(exit_code);
		}
		if (execs->args[2])
		{
			print_custom_error(execs->command, 0, TOO_MANY_ARG);
			sys.last_exit_status_code = 1;
			return ;
		}
	}
	exit(exit_code);
}
