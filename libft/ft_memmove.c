/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:03 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 20:28:38 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	if ((unsigned char *)dst < (unsigned char *)src)
	{
		while (i < len)
		{
			*((unsigned char *)dst + i) \
				= *((unsigned char *)src + i);
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			*((unsigned char *)dst + len - 1 - i) \
				= *((unsigned char *)src + len - 1 - i);
			i++;
		}
	}
	return (dst);
}
