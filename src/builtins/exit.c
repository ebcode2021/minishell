/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 18:49:32 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_long(char *str)
{
	int				sign;
	int				flag;
	unsigned long	temp;

	temp = 0;
	sign = 1;
	flag = 0;
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
		if (temp > LONG_MAX)
			return (0);
		if (temp == LONG_MAX + 1 && sign != -1)
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
			ft_putstr_fd("picoshell: exit: ", STDERR_FILENO);
			ft_putstr_fd(execs->args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(exit_code);
		}
		if (execs->args[2])
		{
			ft_putendl_fd("picoshell: exit: too many arguments", STDERR_FILENO);
			sys.last_exit_status_code = 1;
			return ;
		}
	}
	exit(exit_code);
}
