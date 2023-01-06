/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:44 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/06 14:22:12 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	const char	*builtin_list[8] = \
					{"cd", "echo", "env", "exit", "export", "pwd", "unset", 0};
	int			idx;

	if (!command)
		return (0);
	idx = 0;
	while (builtin_list[idx])
	{
		if (!ft_strncmp(builtin_list[idx], command, ft_strlen(command) + 1))
			return (1);
		idx++;
	}
	return (0);
}

int	check_export_unset_argv(char *arguments, int unset)
{
	size_t	idx;

	idx = 1;
	if (!(ft_isalpha(arguments[0]) || arguments[0] == '_'))
		return (0);
	while (arguments[idx] && (unset || arguments[idx] != '='))
	{
		if (!(ft_isalnum(arguments[idx]) || arguments[idx] == '_'))
			return (0);
		idx++;
	}
	return (1);
}

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
	else if (!ft_strncmp(command_name, "export", 7))
		builtin_export(exec);
	else if (!ft_strncmp(command_name, "exit", 5))
		builtin_exit(exec);
	else if (!ft_strncmp(command_name, "pwd", 4))
		builtin_pwd();
	else
		builtin_unset(exec);
	g_sys.last_exit_status_code = 0;
}
