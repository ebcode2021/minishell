/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:51:04 by eunson            #+#    #+#             */
/*   Updated: 2023/01/02 15:46:12 by eunson           ###   ########.fr       */
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

void	command_handler(t_exec_block *exec)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(exec->command);
	fprintf(stderr,"cmd handler 경로 : %s\n", cmd_path);
	if (!cmd_path)
		error_handler();
	else
		execve(cmd_path, exec->args, (char* const *)&(sys.env_lst));
	sys.last_exit_status_code = 0;
}
