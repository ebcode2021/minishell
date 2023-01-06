/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:59:39 by eunson            #+#    #+#             */
/*   Updated: 2023/01/06 16:00:53 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort(t_list **array)
{
	int		idx;
	int		jdx;
	t_list	*tmp_lst;

	idx = 0;
	while (array[idx])
	{
		jdx = idx + 1;
		while (array[jdx])
		{
			if (ft_strncmp(array[idx]->copy, array[jdx]->copy, BUFFER_SIZE) > 0)
			{
				tmp_lst = array[idx];
				array[idx] = array[jdx];
				array[jdx] = tmp_lst;
				idx = -1;
				break ;
			}
			jdx++;
		}
		idx++;
	}
}

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
