/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:31:46 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/19 19:17:57 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *variable_name, char *value)
{
	t_list	*lstnew;

	lstnew = malloc (sizeof(t_list));
	if (!lstnew)
		return (lstnew);
	lstnew->variable_name = ft_strdup(variable_name);
	lstnew->value = ft_strdup(value);
	lstnew->next = 0;
	return (lstnew);
}
