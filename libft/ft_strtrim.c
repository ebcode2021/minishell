/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:42:55 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 20:07:21 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	set_index(char *s1, char *set, size_t *start, size_t *end)
{
	size_t	i;

	i = 0;
	while (is_set(s1[i], (char *)set))
		i++;
	*start = i;
	i = ft_strlen(s1);
	while (i > 0 && is_set(s1[i - 1], (char *)set))
		i--;
	*end = i;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*res;

	set_index((char *)s1, (char *)set, &start, &end);
	if (end < start)
		len = 0;
	else
		len = end - start;
	res = malloc(len + 1);
	if (!res)
		return (0);
	i = 0;
	while (start + i < end)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
