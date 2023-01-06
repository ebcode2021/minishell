/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:06 by eunson            #+#    #+#             */
/*   Updated: 2023/01/06 16:01:42 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env_lst(void)
{
	size_t	idx;
	t_list	**addrs;

	idx = 0;
	addrs = (t_list **)malloc \
			(sizeof(t_list *) * (ft_lstsize(g_sys.env_lst) + 1));
	save_address(addrs);
	bubble_sort(addrs);
	while (addrs[idx])
	{
		if (ft_strncmp(addrs[idx]->variable_name, "?", 2) != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(addrs[idx]->copy, STDOUT_FILENO);
		}
		idx++;
	}
	free(addrs);
}

static char	*find_variable_name(char *argument)
{
	size_t	idx;
	char	*variable_name;

	idx = 0;
	while (argument[idx] && argument[idx] != '=')
		idx++;
	variable_name = (char *)malloc(sizeof(char) * idx + 1);
	idx = 0;
	while (argument[idx] && argument[idx] != '=')
	{
		variable_name[idx] = argument[idx];
		idx++;
	}
	variable_name[idx] = 0;
	return (variable_name);
}

void	add_export_variable_to_env_lst(char *variable)
{
	char	*variable_name;

	variable_name = find_variable_name(variable);
	ft_lst_remove_if(&g_sys.env_lst, variable_name);
	ft_lstadd_back(&g_sys.env_lst, ft_lstnew(variable));
	free(variable_name);
}

int	builtin_export(t_exec_block *exec)
{
	size_t	idx;
	int		exit_status;

	idx = 1;
	exit_status = 0;
	if (!exec->args[idx])
		print_sorted_env_lst();
	else
	{
		while (exec->args[idx])
		{
			if (check_export_unset_argv(exec->args[idx], EXPORT))
				add_export_variable_to_env_lst(exec->args[idx]);
			else
			{
				exit_status = 1;
				print_custom_error(exec->command, exec->args[idx], NOT_A_VALID);
			}
			idx++;
		}
	}
	return (exit_status);
}
