/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:57:48 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 18:47:30 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	dup = malloc(s1_len + 1);
	if (!dup)
		return (0);
	ft_memmove(dup, (char *)s1, s1_len + 1);
	return (dup);
}
