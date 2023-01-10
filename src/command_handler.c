/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:51:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/10 10:48:49 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_in_envp(void)
{
	t_list	*path_list;

	path_list = ft_lstfind(g_sys.env_lst, "PATH");
	if (!path_list)
		return (0);
	if (path_list->value)
		return (ft_split(path_list->value, ':'));
	else
		return (0);
}

char	*get_cmd_path(char *command)
{
	char	**path_lists;
	char	*cmd_path;
	char	*cmd_path2;
	size_t	idx;

	idx = 0;
	path_lists = get_path_in_envp();
	if (*command == 0)
		print_custom_error(command, 0, COMMAND_NOT_FOUND);
	if (path_lists)
	{
		while (path_lists[idx])
		{
			cmd_path = ft_strjoin(path_lists[idx], "/");
			cmd_path2 = ft_strjoin(cmd_path, command);
			free(cmd_path);
			if (!access(cmd_path2, F_OK))
				return (cmd_path2);
			idx++;
			free(cmd_path2);
		}
	}
	return (0);
}

char	**current_env_lst(void)
{
	char	**env_lst;
	size_t	idx;
	t_list	*head;

	idx = 0;
	env_lst = (char **)malloc(sizeof(char *) * (ft_lstsize(g_sys.env_lst) + 1));
	head = g_sys.env_lst;
	while (head)
	{
		env_lst[idx++] = head->copy;
		head = head->next;
	}
	env_lst[idx] = 0;
	return (env_lst);
}

void	command_execute(t_exec_block *exec, char **env_lst)
{
	char	*cmd_path;
	t_list	*path;

	cmd_path = get_cmd_path(exec->command);
	path = ft_lstfind(g_sys.env_lst, "PATH");
	if (!cmd_path && path && path->value)
		print_custom_error(exec->command, 0, COMMAND_NOT_FOUND);
	else if (!cmd_path)
		print_custom_error(exec->command, 0, NO_SUCH_FILE_DIR);
	else if (execve(cmd_path, exec->args, env_lst) == -1)
		print_error(exec->command, 0);
}

int	command_handler(t_exec_block *exec)
{
	char		**env_lst;
	struct stat	path_stat;

	env_lst = current_env_lst();
	if (stat(exec->command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			print_custom_error(exec->command, 0, IS_DIR);
		else if (S_ISREG(path_stat.st_mode))
		{
			if (execve(exec->command, exec->args, env_lst) == -1)
				print_error(exec->command, 0);
		}
	}
	else if (ft_strchr(exec->command, '/'))
	{
		if (errno == ENOENT)
			print_custom_error(exec->command, 0, NO_SUCH_FILE_DIR);
		else if (errno == ENOTDIR)
			print_custom_error(exec->command, 0, NOT_A_DIR);
	}
	else
		command_execute(exec, env_lst);
	return (g_sys.last_exit_status_code);
}
