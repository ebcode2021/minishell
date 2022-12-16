/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:13:31 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 11:04:49 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	match_index;
	int		match;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = 0;
	match = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			match = 1;
			match_index = i;
		}
		i++;
	}
	if (match)
		return ((char *)s + match_index);
	return (0);
}
