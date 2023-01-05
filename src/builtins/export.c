/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:06 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 13:14:00 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_address(t_list **addrs)
{
	size_t	idx;
	t_list	*head;

	idx = 0;
	head = g_sys.env_lst;
	while (head)
	{
		addrs[idx++] = head;
		head = head->next;
	}
	addrs[idx] = 0;
}

void	bubble_sort(t_list **array)
{
	int		idx;
	int		jdx;
	char	*left_variable;
	char	*right_variable;
	t_list	*tmp_lst;

	idx = 0;
	while (array[idx])
	{
		jdx = idx + 1;
		left_variable = array[idx]->variable_name;
		while (array[jdx])
		{
			right_variable = array[jdx]->variable_name;
			if (ft_strncmp(left_variable, right_variable, BUFFER_SIZE) > 0)
			{
				tmp_lst = array[idx];
				array[idx] = array[jdx];
				array[jdx] = tmp_lst;
			}
			jdx++;
		}
		idx++;
	}
}

void	print_sorted_env_lst(void)
{
	size_t	idx;
	t_list	**addrs;

	idx = 0;
	addrs = (t_list **)malloc(sizeof(t_list *) * (ft_lstsize(g_sys.env_lst) + 1));
	save_address(addrs);
	bubble_sort(addrs);
	while (addrs[idx])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(addrs[idx++]->copy, STDOUT_FILENO);
	}
	free(addrs);
}

char	*find_variable_name(char *argument)
{
	size_t	idx;
	char	*variable_name;

	idx = 0;
	while (argument[idx] != '=')
		idx++;
	variable_name = (char *)malloc(sizeof(char) * idx);
	idx = 0;
	while (argument[idx] != '=')
	{
		variable_name[idx] = argument[idx];
		idx++;
	}
	variable_name[idx] = 0;
	return (variable_name);
}

void	builtin_export(t_exec_block *exec)
{
	size_t	idx;
	t_list	*new_lst;
	char	*variable_name;

	idx = 1;
	if (!exec->args[idx])
		print_sorted_env_lst();
	else
	{
		while (exec->args[idx])
		{
			if (check_export_unset_argv(exec->args[idx], EXPORT))
			{
				variable_name = find_variable_name(exec->args[idx]);
				ft_lst_remove_if(&g_sys.env_lst, variable_name);
				new_lst = ft_lstnew(exec->args[idx]);
				ft_lstadd_back(&g_sys.env_lst, new_lst);
				free(variable_name);
			}
			else
				print_custom_error \
				(exec->command, exec->args[idx], NOT_A_VALID_IDENTIFIER);
			idx++;
		}
	}
}
