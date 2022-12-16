/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:31:46 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/04 22:35:40 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = malloc (sizeof(t_list));
	if (!lstnew)
		return (lstnew);
	lstnew->content = content;
	lstnew->next = 0;
	return (lstnew);
}
