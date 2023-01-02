/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/02 21:41:57 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//kill all process;
// exit_code 직접 세팅..?
//set_exit_code()
//exit(exit code?)

#include "minishell.h"

void	builtin_exit(t_exec_block *block)
{
	size_t	i;
	int		fd;

	//set redirections. does nothing when redirection fails.
	//should not print anything when executed in child process.
	i = 0;
	while (block->args[i])
		i++;
	ft_putstr_fd("exit", fd);
	if (i > 2)
	{
		error_handler();
		//bash: exit: too many arguments.
		sys.last_exit_status_code = 1;
		exit(1);
	}
	if (!is_integer(block->args[0])) //is_long(block->args[0])
		error_handler();
		//bash: exit: 10a: numeric argument required
		//if number is too big it determines as non numeric argument
		//I'm not sure what the range is. -> it's long max :)
		//strange thing is, it still exits even though argument is wrong
	sys.last_exit_status_code = ft_atoi(block->args[0]);
	exit(sys.last_exit_status_code)
}
