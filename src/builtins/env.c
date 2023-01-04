/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:02 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 13:16:30 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	t_list	*head;

	head = sys.env_lst;
	while (head)
	{
		if (head->value)
			ft_putendl_fd(head->copy, STDOUT_FILENO);
		head = head->next;
	}
}
