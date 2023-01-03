/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:51:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/03 15:27:31 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_in_envp(void)
{
	t_list	*path_list;
	
	path_list = ft_lstfind(sys.env_lst, "PATH");
	if (!path_list)
		return (0);
	return (ft_split(path_list->value, ':'));
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

char	**current_env_lst()
{
	char	**env_lst;
	size_t	idx;

	idx = 0;
	env_lst = (char **)malloc(sizeof(char *) * (ft_lstsize(sys.env_lst) + 1));
	while (env_lst[idx])
	{
		env_lst[idx] = ft_strdup(sys.env_lst->variable_name);
		env_lst[idx] = ft_strjoin(env_lst[idx], "=");
		env_lst[idx] = ft_strjoin(env_lst[idx], sys.env_lst->value);
		printf("%s\n", env_lst[idx]);
		idx++;
		
	}
	return (env_lst);
}

void	command_handler(t_exec_block *exec)
{
	char	*cmd_path;
	char	**env_lst;

	cmd_path = get_cmd_path(exec->command);
	env_lst = current_env_lst();
	printf("%s\n", cmd_path);
	if (!cmd_path)
		command_not_found(exec->command);
	else
		execve(cmd_path, exec->args, env_lst);
}
