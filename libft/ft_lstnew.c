/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:31:46 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/08 14:41:27 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(char *envp)
{
	t_list	*lstnew;
	char	**split;
	size_t	idx;

	lstnew = malloc (sizeof(t_list));
	if (!lstnew)
		return (lstnew);
	lstnew->copy = ft_strdup(envp);
	split = ft_split(envp, '=');
	lstnew->variable_name = 0;
	if (split[0])
		lstnew->variable_name = ft_strdup(split[0]);
	lstnew->value = 0;
	if (split[1])
		lstnew->value = ft_strdup(split[1]);
	lstnew->next = 0;
	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);
	return (lstnew);
}
