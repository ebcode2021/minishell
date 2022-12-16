/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:13:38 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/05 02:08:23 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (0);
	ft_memmove(str, (char *)s1, s1_len + 1);
	str = ft_strcat(str, (char *)s2);
	str[s1_len + s2_len] = '\0';
	return (str);
}
