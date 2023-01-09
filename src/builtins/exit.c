/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/09 21:32:01 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_long(char *str)
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

int	builtin_exit(t_exec_block *exec, int child)
{
	int		exit_code;

	exit_code = 0;
	if (!child)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (exec->args[1])
	{
		if (is_long(exec->args[1]))
			exit_code = ft_atoi(exec->args[1]);
		else
		{
			print_custom_error(exec->command, exec->args[1], NUMERIC_ARG);
			exit(0xFF);
		}
		if (exec->args[2])
		{
			print_custom_error(exec->command, 0, TOO_MANY_ARG);
			return (1);
		}
	}
	clean_up();
	exit(exit_code & 0xFF);
	return (0);
}
