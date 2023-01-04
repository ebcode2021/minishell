/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:44 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/04 13:41:10 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	const char *builtin_list[8] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", 0};
	int	idx;

	idx = 0;
	if (!command)
		return (0);
	while (builtin_list[idx])
	{
		if (!ft_strncmp(builtin_list[idx], command, ft_strlen(command) + 1))
			return (1);
		idx++;
	}
	return (0);
}

// cd는 첫 arg
// echo

// export 값이 없어도 보이지만, env는 값이 없으면 안보임.
// void	check_env_arguments(t_exec_block *exec)
// {
	
// }


void	builtin_handler(t_exec_block *exec)
{
	char	*command_name;

	command_name = exec->command;

	if (!ft_strncmp(command_name, "cd", 3))
		builtin_cd(exec);
	else if (!ft_strncmp(command_name, "echo", 5))
		builtin_echo(exec);
	else if (!ft_strncmp(command_name, "env", 4))
		builtin_env();
	// else if (!ft_str ncmp(command_name, "exit", 5))
	// 	builtin_exit(exec);
	// else if (!ft_strncmp(command_name, "export", 7))
	// 	builtin_export(exec);
	else if (!ft_strncmp(command_name, "pwd", 4))
		builtin_pwd();
	// else
	// 	builtin_unset(exec);
}
