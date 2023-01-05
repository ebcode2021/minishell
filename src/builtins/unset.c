/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:10 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 13:14:00 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_exec_block *exec)
{
	size_t	idx;

	idx = 1;
	while (exec->args[idx])
	{
		if (check_export_unset_argv(exec->args[idx], UNSET))
			ft_lst_remove_if(&g_sys.env_lst, exec->args[idx]);
		else
			print_custom_error \
			(exec->command, exec->args[idx], NOT_A_VALID_IDENTIFIER);
		idx++;
	}
}
