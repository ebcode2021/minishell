/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:34:02 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/19 18:38:07 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lst_remove_if(t_list **lst, char *to_find)
{
	t_list	*cur;
	t_list	*tmp;
	size_t	find_len;

	if (!*lst || !to_find)
		return ;
	cur = *lst;
	find_len = ft_strlen(to_find) + 1;
	while (cur->next)
	{
		if (!ft_strncmp(cur->next->variable_name, to_find, find_len))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(tmp, (void *)free);
			return ;
		}
		cur = cur->next;
	}
	cur = *lst;
	if (ft_strncmp(cur->variable_name, to_find, find_len) == 0)
	{
		*lst = cur->next;
		ft_lstdelone(cur, (void *)free);
	}
}
