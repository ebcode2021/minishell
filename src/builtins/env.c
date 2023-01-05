/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:02 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 15:03:22 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	t_list	*head;

	head = g_sys.env_lst;
	while (head)
	{
		if (head->value && *head->variable_name != '?')
			ft_putendl_fd(head->copy, STDOUT_FILENO);
		head = head->next;
	}
}
