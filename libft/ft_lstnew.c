/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:31:46 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/03 16:01:03 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(char *envp)
{
	t_list	*lstnew;
	char	**split;

	split = ft_split(envp, "=");
	lstnew = malloc (sizeof(t_list));
	if (!lstnew)
		return (lstnew);
	lstnew->copy = ft_strdup(envp);
	lstnew->variable_name = ft_strdup(split[0]);
	lstnew->value = ft_strdup(split[1]);
	lstnew->next = 0;
	free_split(split);
	return (lstnew);
}
