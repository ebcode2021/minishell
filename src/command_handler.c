/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:51:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/03 21:06:00 by eunson           ###   ########.fr       */
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
	char	*cmd_path2;
	size_t	idx;

	idx = 0;

	path_lists = get_path_in_envp();
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
	return (0);
}

char	**current_env_lst()
{
	char	**env_lst;
	size_t	idx;
	t_list	*head;

	idx = 0;
	env_lst = (char **)malloc(sizeof(char *) * (ft_lstsize(sys.env_lst) + 1));
	head = sys.env_lst;
	while (head)
	{
		env_lst[idx++] = head->copy;
		head = head->next;
	}
	env_lst[idx] = 0;
	return (env_lst);
}

void	command_handler(t_exec_block *exec)
{
	char	*cmd_path;
	char	**env_lst;

	cmd_path = get_cmd_path(exec->command);
	env_lst = current_env_lst();
	if (!cmd_path)
		command_not_found(exec->command);
	else
		execve(cmd_path, exec->args, env_lst);
}
