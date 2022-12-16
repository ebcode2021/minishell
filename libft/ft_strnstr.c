/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:59:14 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 18:25:09 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	find_len;
	size_t	haystack_len;
	size_t	i;

	haystack_len = ft_strlen((char *)haystack);
	if (!*needle)
		return ((char *)haystack);
	find_len = ft_strlen(needle);
	i = 0;
	while ((i + find_len <= len) && haystack[i])
	{
		if (ft_strncmp(haystack + i, needle, find_len) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
