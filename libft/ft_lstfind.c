/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:26:52 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/19 17:29:26 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, char *str)
{
	while (lst)
	{
		if (ft_strncmp(lst->variable_name, str, ft_strlen(str) + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (0);
}
