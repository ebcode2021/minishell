/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:44 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/27 15:53:59 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	const char *builtin_list[7] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	int	idx;

	idx = 0;
	while (builtin_list[idx++])
	{
		if (!ft_strncmp(*builtin_list, command, ft_strlen(command) + 1))
			return (1);
	}
	return (0);
}

void	builtin_hanlder(t_exec_block *exec)
{
	char	*command_name;

	command_name = exec->command;
	if (!ft_strncmp(command_name, "cd", 3))
		builtin_cd();
	else if (!ft_strncmp(command_name, "echo", 5))
		builtin_echo();
	else if (!ft_strncmp(command_name, "env", 4))
		builtin_env();
	else if (!ft_strncmp(command_name, "exit", 5))
		builtin_exit();
	else if (!ft_strncmp(command_name, "export", 7))
		builtin_export();
	else if (!ft_strncmp(command_name, "pwd", 4))
		builtin_pwd();
	else
		builtin_unset();
}

char	**get_path_in_envp(void)
{
	t_list	*path_list;
	
	path_list = ft_lstfind(sys.env_lst, "PATH");
	if (!path_list)
		return (0);
	return (ft_split(path_list, ':'));
}

char	*get_cmd_path(char *command)
{
	char	**path_lists;
	char	*cmd_path;

	path_lists = get_path_in_envp();
	while (*path_lists)
	{
		cmd_path = (char *)malloc(ft_strlen(*path_lists) + 1);
		cmd_path = ft_strjoin(*path_lists, "/");
		cmd_path = ft_strjoin(cmd_path, command);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path_lists++;
	}
	return (0);
}

void	command_handler(t_exec_block *exec)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(exec->command);
	if (!cmd_path)
		error_handler();
	else
		execve(cmd_path, exec->args, &(sys.env_lst));
	sys.last_exit_status_code = 0;
}
